//
// Created by Luis Vieira on 07/11/2026.
//

#include "Fabrica.h"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include "Aleatorio.h"
#include "Solo.h"
#include "Cratera.h"
#include "Deposito.h"
#include "Posicao.h"
#include "Settings.h"

namespace {
    // Os ficheiros escritos no Windows acabam cada linha em "\r\n"; o getline so corta no '\n'
    void tiraFimDeLinhaWindows(std::string& linha) {
        if (!linha.empty() && linha.back() == '\r') {
            linha.pop_back();
        }
    }
}

Fabrica::Fabrica(int nl, int nc) : nLinhas(nl), nColunas(nc) {
    if (!dimensoesValidas(nl, nc)) {
        throw std::invalid_argument("Fabrica: dimensoes invalidas");
    }
    for (int i = 0; i < nl * nc; ++i) {
        grelha.push_back(new Solo());
    }
}

Fabrica::Fabrica(const Fabrica& outra) : nLinhas(outra.nLinhas), nColunas(outra.nColunas) {
    for (const Terreno* t : outra.grelha) {
        grelha.push_back(t->clona());
    }
}

Fabrica::~Fabrica() {
    for (Terreno* t : grelha) {
        delete t;
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

    // Primeira linha: o numero de linhas e o numero de colunas, e mais nada
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

    // A fabrica e montada num objeto local: se o ficheiro falhar a meio, nada fica criado
    Fabrica fab(nl, nc);
    for (int l = 0; l < nl; ++l) {
        if (!std::getline(ficheiro, linha)) {
            erro = "Mapa: faltam linhas";
            return nullptr;
        }
        tiraFimDeLinhaWindows(linha);
        int tamanho = linha.size();
        if (tamanho != nc) {
            erro = "Mapa: linha com tamanho errado";
            return nullptr;
        }
        for (int c = 0; c < nc; ++c) {
            const char ch = linha[c];
            Terreno* t = criaTerreno(ch);
            if (t == nullptr) {
                erro = "Mapa: caracter invalido";
                return nullptr;
            }
            delete fab.grelha[fab.indice(l, c)];
            fab.grelha[fab.indice(l, c)] = t;
        }
    }

    // Depois do mapa so pode haver linhas vazias
    while (std::getline(ficheiro, linha)) {
        tiraFimDeLinhaWindows(linha);
        if (!linha.empty()) {
            erro = "Mapa: o ficheiro tem linhas a mais";
            return nullptr;
        }
    }

    return new Fabrica(fab);
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

char Fabrica::getCaracter(int l, int c) const {
    return grelha[indice(l, c)]->getCaracter();
}

bool Fabrica::contem(const Posicao& p) const {
    return p.getLinha() >= 0 && p.getLinha() < nLinhas && p.getColuna() >= 0 && p.getColuna() < nColunas;
}

std::string Fabrica::descricaoPosicao(const Posicao& p) const {
    return p.getTexto() + ": " + grelha[indice(p.getLinha(), p.getColuna())]->getDescricao();
}

std::string Fabrica::descricaoArea(const Posicao& centro, int raio) const {
    if (raio < 0) {
        throw std::invalid_argument("Fabrica: raio negativo");
    }
    if (!contem(centro)) {
        throw std::out_of_range("Fabrica: posicao fora da grelha");
    }
    raio = std::min(raio, std::max(nLinhas, nColunas));   // um raio maior nao mostra mais nada

    // O quadrado de raio n a volta do centro, cortado nos limites da grelha
    const int linhaIni = std::max(0, centro.getLinha() - raio);
    const int linhaFim = std::min(nLinhas - 1, centro.getLinha() + raio);
    const int colunaIni = std::max(0, centro.getColuna() - raio);
    const int colunaFim = std::min(nColunas - 1, centro.getColuna() + raio);

    std::ostringstream texto;
    for (int l = linhaIni; l <= linhaFim; ++l) {
        for (int c = colunaIni; c <= colunaFim; ++c) {
            texto << descricaoPosicao(Posicao(l, c)) << '\n';
        }
    }
    return texto.str();
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
    // Recomeca tudo em solo
    for (std::size_t i = 0; i < grelha.size(); ++i) {
        Terreno* solo = new Solo();   // a mesma regra: criar primeiro, apagar depois
        delete grelha[i];
        grelha[i] = solo;
    }

    int livres = nLinhas * nColunas;   // posicoes ainda em solo
    coloca('#', Settings::fabrica_num_crateras, livres);
    coloca('%', Settings::fabrica_num_depositos_ferro, livres);
    coloca('$', Settings::fabrica_num_depositos_silicio, livres);
    coloca('~', Settings::fabrica_num_depositos_gelo, livres);
}

void Fabrica::coloca(char caracter, int quantos, int& livres) {
    for (int i = 0; i < quantos && livres > 0; ++i) {
        // Sorteia posicoes ate encontrar uma que ainda seja solo (' ')
        int pos;
        do {
            pos = Aleatorio::entre(0, nLinhas * nColunas - 1);
        } while (grelha[pos]->getCaracter() != ' ');

        // Cria primeiro e so depois apaga: se o criaTerreno lancar uma excecao, a grelha fica como estava
        Terreno* novo = criaTerreno(caracter);
        delete grelha[pos];
        grelha[pos] = novo;
        if (grelha[pos]->getCaracter() != ' ') {
            --livres;   // so conta se a posicao deixou de ser solo
        }
    }
}
