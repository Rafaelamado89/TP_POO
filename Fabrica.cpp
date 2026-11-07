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
    grelha.resize(nl * nc);
}

// O maximo vem da Settings, mas nunca passa das 26 letras com que se escrevem as posicoes
int Fabrica::maxLinhas() {
    return std::min(Settings::fabrica_max_linhas, Posicao::numLetras);
}

int Fabrica::maxColunas() {
    return std::min(Settings::fabrica_max_colunas, Posicao::numLetras);
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
            Terreno::Tipo tipo = Terreno::Tipo::Solo;
            if (!Terreno::tipoDoMapa(ch, tipo)) {
                erro = std::string("Mapa: caracter invalido '") + ch + "' (codigo " +
                       std::to_string(static_cast<int>(ch)) + ") na linha " + std::to_string(linhaFicheiro) +
                       ", coluna " + std::to_string(c + 1);
                return nullptr;
            }
            fab.grelha[fab.indice(l, c)] = criaTerreno(tipo);
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
    return grelha[indice(l, c)].getCaracter();
}

bool Fabrica::contem(const Posicao& p) const {
    return p.getLinha() >= 0 && p.getLinha() < nLinhas && p.getColuna() >= 0 && p.getColuna() < nColunas;
}

std::string Fabrica::descricaoPosicao(const Posicao& p) const {
    return p.getTexto() + ": " + grelha[indice(p.getLinha(), p.getColuna())].getDescricao();
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

void Fabrica::distribuiAleatorio() {
    grelha.assign(grelha.size(), Terreno());          // recomeça tudo em solo

    std::vector<int> posicoes(grelha.size());
    std::iota(posicoes.begin(), posicoes.end(), 0);   // 0, 1, 2, ..., nl*nc-1
    std::shuffle(posicoes.begin(), posicoes.end(), Aleatorio::gerador());

    std::size_t proxima = 0;
    coloca(Terreno::Tipo::Cratera, Settings::fabrica_num_crateras, posicoes, proxima);
    coloca(Terreno::Tipo::Ferro, Settings::fabrica_num_depositos_ferro, posicoes, proxima);
    coloca(Terreno::Tipo::Silicio, Settings::fabrica_num_depositos_silicio, posicoes, proxima);
    coloca(Terreno::Tipo::Gelo, Settings::fabrica_num_depositos_gelo, posicoes, proxima);
}

Terreno Fabrica::criaTerreno(Terreno::Tipo tipo) {
    if (!Terreno::eDeposito(tipo)) {
        return Terreno(tipo);
    }
    const int qtd = Aleatorio::entre(Settings::deposito_quantidade_min, Settings::deposito_quantidade_max);
    if (qtd < 1) {
        return Terreno();   // um deposito que nasce sem nada ja esta esgotado, e um esgotado passa a solo
    }
    return Terreno(tipo, qtd);
}

void Fabrica::coloca(Terreno::Tipo tipo, int quantos, const std::vector<int> &posicoes, std::size_t &proxima) {
    for (int i = 0; i < quantos && proxima < posicoes.size(); ++i) {
        grelha[posicoes[proxima]] = criaTerreno(tipo);
        ++proxima;
    }
}
