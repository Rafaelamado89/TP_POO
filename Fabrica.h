//
// Created by Luis Vieira on 07/11/2026.
//

#ifndef FABRICA_H
#define FABRICA_H

#include <string>
#include <vector>
#include "Terreno.h"

class Posicao;

class Fabrica {
public:
    explicit Fabrica(int nl, int nc);

    static bool dimensoesValidas(int nl, int nc);
    static Fabrica* carrega(const std::string& nomeFicheiro, std::string& erro);

    int getLinhas() const;
    int getColunas() const;
    char getCaracter(int l, int c) const;

    bool contem(const Posicao& p) const;
    std::string descricaoPosicao(const Posicao& p) const;
    std::string descricaoArea(const Posicao& centro, int raio) const;

    void distribuiAleatorio();

private:
    int nLinhas;
    int nColunas;
    std::vector<Terreno> grelha;

    int indice(int l, int c) const;

    static int maxLinhas();
    static int maxColunas();
    static Terreno criaTerreno(Terreno::Tipo tipo);
    void coloca(Terreno::Tipo tipo, int quantos, const std::vector<int>& posicoes, std::size_t& proxima);
};


#endif //FABRICA_H
