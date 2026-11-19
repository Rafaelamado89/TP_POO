#include "Vista.h"

#include <algorithm>
#include <string>
#include "Ecra.h"
#include "Fabrica.h"

void Vista::mostra(const Fabrica& fab, int instante, int creditos, int numMaquinas, int numEngenheiros) {
    // O ecra virtual tem de ter espaco para a fabrica e para o painel, lado a lado
    const int altura = std::max(alturaFabrica(fab), painelAlturaMin);
    const int colunaPainel = larguraFabrica(fab) + espacoPainel;

    Ecra e(altura, colunaPainel + painelLargura);
    desenhaFabrica(e, fab);
    desenhaPainel(e, colunaPainel, altura, instante, creditos, numMaquinas, numEngenheiros);
    e.mostra();
}

// moldura, regua das colunas, uma linha do ecra por linha da fabrica, uma linha vazia, moldura
int Vista::alturaFabrica(const Fabrica& fab) {
    return fab.getLinhas() + 4;
}

// moldura, regua das linhas, espaco, uma coluna do ecra por coluna da fabrica, espaco, moldura
int Vista::larguraFabrica(const Fabrica& fab) {
    return fab.getColunas() + 5;
}

void Vista::desenhaFabrica(Ecra& e, const Fabrica& fab) {
    e.moldura(0, 0, alturaFabrica(fab), larguraFabrica(fab));

    // Regua: as letras das posicoes, em maiusculas para nao se confundirem com o conteudo
    for (int c = 0; c < fab.getColunas(); ++c) {
        e.escreve(grelhaLinha - 1, grelhaColuna + c, static_cast<char>('A' + c));
    }
    for (int l = 0; l < fab.getLinhas(); ++l) {
        e.escreve(grelhaLinha + l, grelhaColuna - 2, static_cast<char>('A' + l));
    }

    // Um caracter por posicao: a posicao (l, c) da fabrica fica no ecra em (grelhaLinha + l, grelhaColuna + c)
    for (int l = 0; l < fab.getLinhas(); ++l) {
        for (int c = 0; c < fab.getColunas(); ++c) {
            e.escreve(grelhaLinha + l, grelhaColuna + c, fab.getCaracter(l, c));
        }
    }
}

void Vista::desenhaPainel(Ecra& e, int coluna, int altura, int instante, int creditos, int numMaquinas,
                          int numEngenheiros) {
    e.moldura(0, coluna, altura, painelLargura);
    e.escreve(1, coluna + 2, "Instante: " + std::to_string(instante));
    e.escreve(2, coluna + 2, "Creditos: " + std::to_string(creditos));
    e.escreve(3, coluna + 2, "Maquinas: " + std::to_string(numMaquinas));
    e.escreve(4, coluna + 2, "Engenheiros: " + std::to_string(numEngenheiros));
}
