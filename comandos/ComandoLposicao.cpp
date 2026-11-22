#include "ComandoLposicao.h"

#include <sstream>
#include <string>
#include "Fabrica.h"
#include "Posicao.h"
#include "Simulador.h"

ComandoLposicao::ComandoLposicao() : Comando("lposicao", "lposicao <lc> [n]") {
}

bool ComandoLposicao::executa(Simulador& sim, std::istringstream& args) {
    std::string txtPosicao, txtRaio;
    if (!(args >> txtPosicao)) {
        return erroSintaxe(sim);
    }
    int raio = 0;
    if (args >> txtRaio) {
        if (!semMaisParametros(args)) {
            return erroSintaxe(sim);
        }
        if (!paraInteiro(txtRaio, raio) || raio < 0) {
            sim.informa("O raio tem de ser um inteiro maior ou igual a 0 (ex.: lposicao df 2)");
            return false;
        }
    }
    Posicao p;
    if (!posicaoNaFabrica(sim, txtPosicao, p)) {
        return false;
    }
    sim.informa(sim.getFabrica().descricaoArea(p, raio));
    return true;
}

std::string ComandoLposicao::getAjuda() const {
    return formataAjuda(
        "<lc> a posicao, linha e coluna (ex.: df); [n] um raio (inteiro maior ou igual a 0, opcional)",
        "mostra o terreno da posicao (e a quantidade de materia-prima, se for um deposito) e toda a informacao "
        "da maquina que la estiver; com n, mostra todas as posicoes do quadrado de raio n centrado em lc",
        "ainda nao ha fabrica; falta a posicao ou ha parametros a mais; posicao invalida ou fora da fabrica; "
        "n nao e um inteiro maior ou igual a 0",
        "lposicao df 2");
}
