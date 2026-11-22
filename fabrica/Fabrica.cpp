//
// Created by Luis Vieira on 07/11/2026.
//

#include "Fabrica.h"

#include <algorithm>
#include <exception>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include "Aleatorio.h"
#include "Cratera.h"
#include "Deposito.h"
#include "Maquina.h"
#include "Posicao.h"
#include "Settings.h"
#include "Solo.h"
#include "Terreno.h"

namespace {
    // Os ficheiros escritos no Windows acabam cada linha em "\r\n"; o getline so corta no '\n'
    void tiraFimDeLinhaWindows(std::string& linha) {
        if (!linha.empty() && linha.back() == '\r') {
            linha.pop_back();
        }
    }

    char letraDirecao(Direcao d) {
        switch (d) {
            case Cima:
                return 'c';
            case Baixo:
                return 'b';
            case Esquerda:
                return 'e';
            case Direita:
                return 'd';
        }
        return '?';
    }

    const char simbolosItens[] = {'f', 's', 'g', 'p', 'i', 'a', 'k'};
    const std::string nomesItens[] = {"minerio de ferro", "silicio bruto", "gelo", "placa de ferro",
                                      "silicio puro", "agua", "kit de habitat"};
}

Fabrica::Fabrica(int nl, int nc)
    : nLinhas(nl), nColunas(nc), creditos(Settings::fabrica_creditos_iniciais), instante(0), enviados{} {
    if (!dimensoesValidas(nl, nc)) {
        throw std::invalid_argument("Fabrica: dimensoes invalidas");
    }
    for (int i = 0; i < nl * nc; ++i) {
        grelha.push_back(new Solo());
        maquinas.push_back(nullptr);
    }
}

Fabrica::~Fabrica() {
    for (Terreno* t : grelha) {
        delete t;
    }
    for (Maquina* m : maquinas) {
        delete m;
    }
}

int Fabrica::maxLinhas() {
    if (Settings::fabrica_max_linhas < Posicao::numLetras)
        return Settings::fabrica_max_linhas;
    return Posicao::numLetras;
}

int Fabrica::maxColunas() {
    if (Settings::fabrica_max_colunas < Posicao::numLetras)
        return Settings::fabrica_max_colunas;
    return Posicao::numLetras;
}

bool Fabrica::dimensoesValidas(int nl, int nc) {
    return nl >= 1 && nl <= maxLinhas() && nc >= 1 && nc <= maxColunas();
}

Fabrica* Fabrica::carrega(const std::string& nomeFicheiro, std::string& erro) {
    std::ifstream ficheiro(nomeFicheiro);
    if (!ficheiro) {
        erro = "Mapa: nao foi possivel abrir o ficheiro";
        return nullptr;
    }

    std::string linha;
    if (!std::getline(ficheiro, linha)) {
        erro = "Mapa: o ficheiro esta vazio";
        return nullptr;
    }
    tiraFimDeLinhaWindows(linha);
    std::istringstream dimensoes(linha);
    int nl = 0, nc = 0;
    std::string resto;
    if (!(dimensoes >> nl >> nc) || (dimensoes >> resto)) {
        erro = "Mapa: primeira linha invalida";
        return nullptr;
    }
    if (!dimensoesValidas(nl, nc)) {
        erro = "Mapa: dimensoes invalidas";
        return nullptr;
    }

    // A fabrica so e devolvida se o mapa estiver todo certo; se nao, e apagada aqui e nada fica criado
    Fabrica* fab = new Fabrica(nl, nc);
    bool lido = false;
    try {
        lido = fab->leMapa(ficheiro, erro);
    } catch (const std::exception&) {
        delete fab;
        throw;
    }
    if (!lido) {
        delete fab;
        return nullptr;
    }
    return fab;
}

bool Fabrica::leMapa(std::istream& ficheiro, std::string& erro) {
    std::string linha;
    for (int l = 0; l < nLinhas; ++l) {
        if (!std::getline(ficheiro, linha)) {
            erro = "Mapa: faltam linhas";
            return false;
        }
        tiraFimDeLinhaWindows(linha);
        const int tamanho = linha.size();
        if (tamanho != nColunas) {
            erro = "Mapa: linha com tamanho errado";
            return false;
        }
        for (int c = 0; c < nColunas; ++c) {
            Terreno* t = criaTerreno(linha[c]);
            if (t == nullptr) {
                erro = "Mapa: caracter invalido";
                return false;
            }
            delete grelha[indice(l, c)];
            grelha[indice(l, c)] = t;
        }
    }

    while (std::getline(ficheiro, linha)) {
        tiraFimDeLinhaWindows(linha);
        if (!linha.empty()) {
            erro = "Mapa: o ficheiro tem linhas a mais";
            return false;
        }
    }
    return true;
}

Terreno* Fabrica::criaTerreno(char caracter) {
    std::string nome;
    switch (caracter) {
        case '.':
            return new Solo();
        case '#':
            return new Cratera();
        case '%':
            nome = "ferro";
            break;
        case '$':
            nome = "silicio";
            break;
        case '~':
            nome = "gelo";
            break;
        default:
            return nullptr;
    }
    const int qtd = Aleatorio::entre(Settings::deposito_quantidade_min, Settings::deposito_quantidade_max);
    if (qtd < 1) {
        return new Solo();   // um deposito que nasce sem nada ja esta esgotado, e um esgotado passa a solo
    }
    return new Deposito(caracter, nome, qtd);
}

void Fabrica::distribuiAleatorio() {
    for (std::size_t i = 0; i < grelha.size(); ++i) {
        Terreno* solo = new Solo();
        delete grelha[i];
        grelha[i] = solo;
    }

    int livres = nLinhas * nColunas;
    coloca('#', Settings::fabrica_num_crateras, livres);
    coloca('%', Settings::fabrica_num_depositos_ferro, livres);
    coloca('$', Settings::fabrica_num_depositos_silicio, livres);
    coloca('~', Settings::fabrica_num_depositos_gelo, livres);
}

void Fabrica::coloca(char caracter, int quantos, int& livres) {
    for (int i = 0; i < quantos && livres > 0; ++i) {
        int pos;
        do {
            pos = Aleatorio::entre(0, nLinhas * nColunas - 1);
        } while (grelha[pos]->getCaracter() != ' ');

        // Cria primeiro e so depois apaga: se o criaTerreno lancar uma excecao, a grelha fica como estava
        Terreno* novo = criaTerreno(caracter);
        delete grelha[pos];
        grelha[pos] = novo;
        if (grelha[pos]->getCaracter() != ' ') {
            --livres;
        }
    }
}

int Fabrica::getLinhas() const {
    return nLinhas;
}

int Fabrica::getColunas() const {
    return nColunas;
}

int Fabrica::indice(int l, int c) const {
    if (l < 0 || l >= nLinhas || c < 0 || c >= nColunas) {
        throw std::out_of_range("Fabrica: posicao fora da grelha");
    }
    return l * nColunas + c;
}

int Fabrica::indice(const Posicao& p) const {
    return indice(p.getLinha(), p.getColuna());
}

char Fabrica::getCaracter(int l, int c) const {
    const int i = indice(l, c);
    if (maquinas[i] != nullptr) {
        return maquinas[i]->getSimbolo();
    }
    return grelha[i]->getCaracter();
}

bool Fabrica::contem(const Posicao& p) const {
    return p.getLinha() >= 0 && p.getLinha() < nLinhas && p.getColuna() >= 0 && p.getColuna() < nColunas;
}

std::string Fabrica::descricaoMaquina(int i) const {
    const Maquina* m = maquinas[i];
    std::string texto = std::string(1, m->getSimbolo()) + ", saida " + letraDirecao(m->getSaida()) + ", " +
                        std::to_string(m->getNumEngenheiros()) + " engenheiros";
    const std::string propria = m->getDescricao();
    if (!propria.empty()) {
        texto += "; " + propria;
    }
    return texto;
}

std::string Fabrica::descricaoPosicao(const Posicao& p) const {
    const int i = indice(p);
    std::string texto = p.getTexto() + ": " + grelha[i]->getDescricao();
    if (maquinas[i] != nullptr) {
        texto += " | maquina " + descricaoMaquina(i);
    }
    return texto;
}

std::string Fabrica::descricaoArea(const Posicao& centro, int raio) const {
    if (raio < 0) {
        throw std::invalid_argument("Fabrica: raio negativo");
    }
    if (!contem(centro)) {
        throw std::out_of_range("Fabrica: posicao fora da grelha");
    }
    raio = std::min(raio, std::max(nLinhas, nColunas));

    const int linhaIni = std::max(0, centro.getLinha() - raio);
    const int linhaFim = std::min(nLinhas - 1, centro.getLinha() + raio);
    const int colunaIni = std::max(0, centro.getColuna() - raio);
    const int colunaFim = std::min(nColunas - 1, centro.getColuna() + raio);

    std::ostringstream texto;
    for (int l = linhaIni; l <= linhaFim; ++l) {
        for (int c = colunaIni; c <= colunaFim; ++c) {
            if (l != linhaIni || c != colunaIni) {
                texto << '\n';
            }
            texto << descricaoPosicao(Posicao(l, c));
        }
    }
    return texto.str();
}

std::string Fabrica::descricaoEstado() const {
    std::ostringstream texto;
    texto << "Instante: " << instante << '\n'
          << "Creditos: " << creditos << '\n'
          << "Maquinas: " << getNumMaquinas();
    for (int l = 0; l < nLinhas; ++l) {
        for (int c = 0; c < nColunas; ++c) {
            if (maquinas[indice(l, c)] != nullptr) {
                texto << "\n  " << Posicao(l, c).getTexto() << ": " << descricaoMaquina(indice(l, c));
            }
        }
    }
    texto << "\nEngenheiros: " << getNumEngenheiros()
          << "\nItens enviados para a Terra desde o inicio:";
    for (int t = 0; t < numTiposItem; ++t) {
        texto << "\n  " << simbolosItens[t] << " (" << nomesItens[t] << "): " << enviados[t];
    }
    return texto.str();
}

int Fabrica::getInstante() const {
    return instante;
}

int Fabrica::getCreditos() const {
    return creditos;
}

int Fabrica::getNumMaquinas() const {
    int n = 0;
    for (const Maquina* m : maquinas) {
        if (m != nullptr) {
            ++n;
        }
    }
    return n;
}

int Fabrica::getNumEngenheiros() const {
    return 0;
}

const std::string& Fabrica::getResumoUltimoInstante() const {
    return resumoUltimoInstante;
}

bool Fabrica::compra(Maquina* nova, const Posicao& p, std::string& erro) {
    if (nova == nullptr) {
        throw std::invalid_argument("Fabrica: compra sem maquina");
    }
    if (!contem(p)) {
        erro = "a posicao " + p.getTexto() + " fica fora da fabrica";
    } else if (grelha[indice(p)]->getCaracter() == '#') {
        erro = "a posicao " + p.getTexto() + " e uma cratera";
    } else if (maquinas[indice(p)] != nullptr) {
        erro = "a posicao " + p.getTexto() + " ja esta ocupada";
    } else if (nova->getCusto() > creditos) {
        erro = "creditos insuficientes (custa " + std::to_string(nova->getCusto()) + ", ha " +
               std::to_string(creditos) + ")";
    } else {
        creditos -= nova->getCusto();
        maquinas[indice(p)] = nova;
        return true;
    }
    delete nova;
    return false;
}

Maquina* Fabrica::getMaquina(const Posicao& p) {
    if (!contem(p)) {
        return nullptr;
    }
    return maquinas[indice(p)];
}

const Maquina* Fabrica::getMaquina(const Posicao& p) const {
    if (!contem(p)) {
        return nullptr;
    }
    return maquinas[indice(p)];
}

bool Fabrica::removeMaquina(const Posicao& p) {
    if (!contem(p) || maquinas[indice(p)] == nullptr) {
        return false;
    }
    delete maquinas[indice(p)];
    maquinas[indice(p)] = nullptr;
    return true;
}

void Fabrica::recebeCreditos(int quantia) {
    if (quantia < 0) {
        throw std::invalid_argument("Fabrica: quantia negativa");
    }
    creditos += quantia;
}

Maquina* Fabrica::destinoDe(int l, int c) const {
    int lv = l;
    int cv = c;
    switch (maquinas[indice(l, c)]->getSaida()) {
        case Cima:
            --lv;
            break;
        case Baixo:
            ++lv;
            break;
        case Esquerda:
            --cv;
            break;
        case Direita:
            ++cv;
            break;
    }
    if (lv < 0 || lv >= nLinhas || cv < 0 || cv >= nColunas) {
        return nullptr;
    }
    return maquinas[indice(lv, cv)];
}

// Um item avanca no maximo uma posicao por instante: a maquina que acabou de receber um item fica marcada
// (marcaAtividade) e so o entrega no instante seguinte; no fim do instante o fimInstante limpa as marcas.
void Fabrica::avancaInstante() {
    ++instante;
    std::string resumo;

    for (int l = 0; l < nLinhas; ++l) {
        for (int c = 0; c < nColunas; ++c) {
            Maquina* m = maquinas[indice(l, c)];
            if (m != nullptr) {
                m->atua(destinoDe(l, c), grelha[indice(l, c)]);
            }
        }
    }

    for (Maquina* m : maquinas) {
        if (m != nullptr) {
            m->fimInstante();
        }
    }

    resumoUltimoInstante = resumo;
}
