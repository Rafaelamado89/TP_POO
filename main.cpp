#include "Settings.h"
#include "Ecra.h"

int main() {
    // Tamanho da fabrica (mais tarde vem da classe Fabrica)
    const int nl = 8, nc = 5;

    // Tamanhos no ecra
    const int fabAltura = nl + 3;       // borda + regua + grelha + borda
    const int fabLargura = nc + 3;
    const int painelCol = fabLargura + 1;
    const int painelLargura = 34;

    Ecra e(fabAltura, painelCol + painelLargura);

    // Fabrica: moldura + regua
    e.moldura(0, 0, fabAltura, fabLargura);
    e.regua(1, 1, nl, nc);

    // Exemplo de conteudo: posicao (l, c) da fabrica fica no ecra em (2 + l, 2 + c)
    e.posiciona(2 + 2, 2 + 3);
    e.escreve("%P>f>R");

    // Painel de estado: moldura + texto
    e.moldura(0, painelCol, fabAltura, painelLargura);
    e.posiciona(1, painelCol + 2);
    e.escreve("Instante: 0");
    e.posiciona(2, painelCol + 2);
    e.escreve("Creditos: 1000");

    e.mostra();
    return 0;
}