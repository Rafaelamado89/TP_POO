//
// Created by Luis Vieira on 07/11/2026.
//

#ifndef FABRICA_H
#define FABRICA_H

#include <vector>
#include "Terreno.h"

class Fabrica {
public:
    explicit Fabrica(int nl, int nc);

    int getLinhas() const;
    int getColunas() const;
    char getCaracter(int l, int c) const;

    void distribuiAleatorio();

private:
    int nLinhas;
    int nColunas;
    std::vector<Terreno> grelha;

    int indice(int l, int c) const;

    void coloca(Terreno::Tipo tipo, int quantos, const std::vector<int>& posicoes, std::size_t& proxima);
};


#endif //FABRICA_H
