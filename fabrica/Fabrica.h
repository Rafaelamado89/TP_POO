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
    ~Fabrica();
    Fabrica(const Fabrica& outra);

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
    std::vector<Terreno*> grelha;   // um ponteiro por posicao (a fabrica e a dona)

    int indice(int l, int c) const;

    static int maxLinhas();
    static int maxColunas();
    // Cria o terreno que corresponde ao caracter do mapa ('.', '#', '%', '$', '~'); nullptr se for invalido
    static Terreno* criaTerreno(char caracter);
    void coloca(char caracter, int quantos, int& livres);
};


#endif //FABRICA_H
