#include "Vista.h"

#include <algorithm>
#include <sstream>
#include <string>
#include "Ecra.h"
#include "Fabrica.h"
#include "Settings.h"

namespace {
    // Quantas linhas tem um texto (o resumo do ultimo instante tem uma por acontecimento)
    int contaLinhas(const std::string& texto) {
        std::istringstream is(texto);
        std::string linha;
        int n = 0;
        while (std::getline(is, linha)) {
            ++n;
        }
        return n;
    }
}

void Vista::mostra(const Fabrica& fab) {
    // O ecra virtual tem de ter espaco para a fabrica e para o painel, lado a lado. O painel cresce com o
    // resumo do ultimo instante (uma linha por acontecimento), ate ao tamanho maximo do ecra.
    const int alturaPainel = std::max(painelAlturaMin, linhaResumo + contaLinhas(fab.getResumoUltimoInstante()) + 1);
    const int altura = std::min(std::max(alturaFabrica(fab), alturaPainel), Settings::ecra_max_linhas);
    const int colunaPainel = larguraFabrica(fab) + espacoPainel;

    Ecra e(altura, colunaPainel + painelLargura);
    desenhaFabrica(e, fab);
    desenhaPainel(e, fab, colunaPainel, altura);
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

void Vista::desenhaPainel(Ecra& e, const Fabrica& fab, int coluna, int altura) {
    e.moldura(0, coluna, altura, painelLargura);
    e.escreve(1, coluna + 2, "Instante: " + std::to_string(fab.getInstante()));
    e.escreve(2, coluna + 2, "Creditos: " + std::to_string(fab.getCreditos()));
    e.escreve(3, coluna + 2, "Maquinas: " + std::to_string(fab.getNumMaquinas()));
    e.escreve(4, coluna + 2, "Engenheiros: " + std::to_string(fab.getNumEngenheiros()));
    e.escreve(6, coluna + 2, "No ultimo instante:");

    // O resumo vem com uma linha por acontecimento; cabem as linhas ate a moldura de baixo.
    // Se nem com o ecra no tamanho maximo couberem todas, a ultima diz quantas ficaram de fora.
    const std::string& resumo = fab.getResumoUltimoInstante();
    if (resumo.empty()) {
        e.escreve(linhaResumo, coluna + 2, "nada a assinalar");
        return;
    }
    const int total = contaLinhas(resumo);
    const int cabem = altura - 1 - linhaResumo;
    std::istringstream linhas(resumo);
    std::string linha;
    for (int i = 0; i < cabem && std::getline(linhas, linha); ++i) {
        if (i == cabem - 1 && total > cabem) {
            linha = "(mais " + std::to_string(total - i) + " acontecimentos)";
        }
        e.escreve(linhaResumo + i, coluna + 2, linha.substr(0, painelLargura - 4));   // sem tapar a moldura
    }
}
