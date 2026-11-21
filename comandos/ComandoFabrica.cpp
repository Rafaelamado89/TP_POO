#include "ComandoFabrica.h"

#include <exception>
#include <sstream>
#include <string>
#include "Fabrica.h"
#include "Simulador.h"

ComandoFabrica::ComandoFabrica() : Comando("fabrica", "fabrica <nl> <nc>") {
}

// E ele que cria a fabrica: corre sem ela (e recusa-se se ja existir)
bool ComandoFabrica::precisaFabrica() const {
    return false;
}

bool ComandoFabrica::executa(Simulador& sim, std::istringstream& args) {
    if (sim.temFabrica()) {
        sim.informa("A fabrica ja foi criada: fabrica e carrega so podem ser usados uma vez");
        return false;
    }

    std::string txtLinhas, txtColunas;
    if (!(args >> txtLinhas >> txtColunas) || !semMaisParametros(args)) {
        return erroSintaxe(sim);
    }
    int nl = 0, nc = 0;
    if (!paraInteiro(txtLinhas, nl) || !paraInteiro(txtColunas, nc)) {
        sim.informa("O numero de linhas e o de colunas tem de ser inteiros (ex.: fabrica 12 20)");
        return false;
    }
    if (!Fabrica::dimensoesValidas(nl, nc)) {
        sim.informa("Dimensoes invalidas: linhas de 1 a " + std::to_string(Fabrica::maxLinhas()) +
                    " e colunas de 1 a " + std::to_string(Fabrica::maxColunas()));
        return false;
    }

    Fabrica* nova = new Fabrica(nl, nc);
    try {
        nova->distribuiAleatorio();
    } catch (const std::exception&) {
        delete nova;   // nao fica uma fabrica meio feita, nem fugas; o processa trata do erro
        throw;
    }
    sim.instalaFabrica(nova);
    sim.mostraEcra();
    return true;
}

std::string ComandoFabrica::getAjuda() const {
    return formataAjuda(
        "<nl> numero de linhas e <nc> numero de colunas (inteiros, linhas de 1 a " +
        std::to_string(Fabrica::maxLinhas()) + " e colunas de 1 a " + std::to_string(Fabrica::maxColunas()) + ")",
        "cria a fabrica com essas dimensoes e coloca as crateras e os depositos em posicoes aleatorias, nas "
        "quantidades da configuracao. Ele ou o carrega tem de ser o primeiro comando executado com sucesso.",
        "a fabrica ja existe; faltam ou sobram parametros; nl ou nc nao sao inteiros ou estao fora dos limites",
        "fabrica 12 20");
}
