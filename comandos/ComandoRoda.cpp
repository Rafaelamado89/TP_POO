#include "ComandoRoda.h"

#include <sstream>
#include <string>
#include "Fabrica.h"
#include "Maquina.h"
#include "Posicao.h"
#include "Simulador.h"

ComandoRoda::ComandoRoda() : Comando("roda", "roda <lc> <dir>") {
}

bool ComandoRoda::executa(Simulador& sim, std::istringstream& args) {
    std::string txtPosicao, txtDirecao;
    if (!(args >> txtPosicao >> txtDirecao) || !semMaisParametros(args)) {
        return erroSintaxe(sim);
    }
    Posicao p;
    if (!posicaoNaFabrica(sim, txtPosicao, p)) {
        return false;
    }
    Direcao saida = Direita;
    if (!paraDirecao(txtDirecao, saida)) {
        sim.informa("Direcao invalida: '" + txtDirecao + "' (c, b, e ou d)");
        return false;
    }

    Maquina* m = sim.getFabrica().getMaquina(p);
    if (m == nullptr) {
        sim.informa("Nao ha nenhuma maquina na posicao " + txtPosicao);
        return false;
    }

    m->setSaida(saida);
    sim.mostraEcra();
    return true;
}

std::string ComandoRoda::getAjuda() const {
    return formataAjuda(
        "<lc> a posicao da maquina, linha e coluna (ex.: ce); "
        "<dir> a nova direcao de saida: c (cima), b (baixo), e (esquerda) ou d (direita)",
        "muda a direcao de saida da maquina dessa posicao",
        "ainda nao ha fabrica; faltam ou sobram parametros; posicao invalida ou fora da fabrica; direcao "
        "invalida; nao ha maquina nessa posicao",
        "roda ce b");
}
