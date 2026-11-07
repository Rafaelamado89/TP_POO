//
// Created by Luis Vieira on 07/11/2026.
//

#include "Fabrica.h"

#include <algorithm>
#include <fstream>
#include <numeric>
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
        throw std::invalid_argument("Fabrica: dimensoes invalidas " + std::to_string(nl) + "x" + std::to_string(nc) +
                                    " (minimo 1x1, maximo " + std::to_string(maxLinhas()) + "x" +
                                    std::to_string(maxColunas()) + ")");
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
        erro = "Mapa: nao foi possivel abrir o ficheiro '" + nomeFicheiro + "'";
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
        erro = "Mapa: a primeira linha deve ter apenas o numero de linhas e o numero de colunas";
        return nullptr;
    }
    if (!dimensoesValidas(nl, nc)) {
        erro = "Mapa: dimensoes invalidas " + std::to_string(nl) + "x" + std::to_string(nc) +
               " (minimo 1x1, maximo " + std::to_string(maxLinhas()) + "x" + std::to_string(maxColunas()) + ")";
        return nullptr;
    }

    // A fabrica e montada num objeto local: se o ficheiro falhar a meio, nada fica criado
    Fabrica fab(nl, nc);
    for (int l = 0; l < nl; ++l) {
        const int linhaFicheiro = l + 2;
        if (!std::getline(ficheiro, linha)) {
            erro = "Mapa: faltam linhas (indicadas " + std::to_string(nl) + ", encontradas " + std::to_string(l) + ")";
            return nullptr;
        }
        tiraFimDeLinhaWindows(linha);
        if (linha.size() != static_cast<std::size_t>(nc)) {
            erro = "Mapa: a linha " + std::to_string(linhaFicheiro) + " tem " + std::to_string(linha.size()) +
                   " caracteres em vez de " + std::to_string(nc);
            return nullptr;
        }
        for (int c = 0; c < nc; ++c) {
            const char ch = linha[static_cast<std::size_t>(c)];
            Terreno* t = criaTerreno(ch);
            if (t == nullptr) {
                erro = "Mapa: caracter invalido";          // caracter invalido
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
            erro = "Mapa: o ficheiro tem mais linhas do que as " + std::to_string(nl) + " indicadas";
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
        throw std::out_of_range(
            "Fabrica: posicao (" + std::to_string(l) + ", " + std::to_string(c) + ") fora da grelha " +
            std::to_string(nLinhas) + "x" + std::to_string(nColunas));
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
        throw std::invalid_argument("Fabrica: raio negativo (" + std::to_string(raio) + ")");
    }
    if (!contem(centro)) {
        throw std::out_of_range("Fabrica: posicao " + centro.getTexto() + " fora da grelha " +
                                std::to_string(nLinhas) + "x" + std::to_string(nColunas));
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
        delete grelha[i];
        grelha[i] = new Solo();
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

        delete grelha[pos];
        grelha[pos] = criaTerreno(caracter);
        if (grelha[pos]->getCaracter() != ' ') {
            --livres;   // so conta se a posicao deixou de ser solo
        }
    }
}
