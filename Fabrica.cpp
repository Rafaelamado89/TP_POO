//
// Created by Luis Vieira on 07/11/2026.
//

#include "Fabrica.h"

#include <algorithm>
#include <numeric>
#include <stdexcept>
#include "Settings.h"
#include <string>
#include "Aleatorio.h"
#include <numeric>

Fabrica::Fabrica(int nl, int nc) : nLinhas(nl), nColunas(nc) {
    if (nl > Settings::fabrica_max_linhas || nc > Settings::fabrica_max_colunas || nl < 1 || nc < 1) {
        throw std::invalid_argument("Fabrica: dimensoes invalidas " + std::to_string(nl) + "x" + std::to_string(nc) +
                                    " (minimo 1x1, maximo " + std::to_string(Settings::fabrica_max_linhas) + "x" +
                                    std::to_string(Settings::fabrica_max_colunas) + ")");
    }
    grelha.resize(nl * nc);
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

void Fabrica::coloca(Terreno::Tipo tipo, int quantos, const std::vector<int> &posicoes, std::size_t &proxima) {
    for (int i = 0; i < quantos && proxima < posicoes.size(); ++i) {
        int qtd = 0;
        if (tipo != Terreno::Tipo::Cratera) {
            qtd = Aleatorio::entre(Settings::deposito_quantidade_min, Settings::deposito_quantidade_max);
        }
        grelha[posicoes[proxima]] = Terreno(tipo, qtd);
        ++proxima;
    }
}
