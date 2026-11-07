//
// Created by Luis Vieira on 07/11/2026.
//

#include "Fabrica.h"
#include <stdexcept>
#include "Settings.h"
#include <string>

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
