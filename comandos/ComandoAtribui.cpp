#include "ComandoAtribui.h"

#include <sstream>
#include <string>
#include "Posicao.h"
#include "Simulador.h"

ComandoAtribui::ComandoAtribui() : Comando("atribui", "atribui <id> <lc>") {
}

bool ComandoAtribui::executa(Simulador& sim, std::istringstream& args) {
    std::string txtId, txtPosicao;
    if (!(args >> txtId >> txtPosicao) || !semMaisParametros(args)) {
        return erroSintaxe(sim);
    }
    int id = 0;
    if (!paraInteiro(txtId, id) || id < 1) {
        sim.informa("O numero do engenheiro tem de ser um inteiro positivo (ex.: atribui 2 hr)");
        return false;
    }
    Posicao p;
    if (!posicaoNaFabrica(sim, txtPosicao, p)) {
        return false;
    }
    sim.informa("atribui " + txtId + " " + txtPosicao +
                ": parametros validos, mas este comando ainda nao tem efeito nesta versao");
    return true;
}

std::string ComandoAtribui::getAjuda() const {
    return formataAjuda(
        "<id> o numero do engenheiro (inteiro positivo); <lc> a posicao da maquina, linha e coluna (ex.: hr)",
        "associa o engenheiro a maquina dessa posicao; se estava associado a outra, deixa de estar. "
        "Nesta versao so valida os parametros.",
        "ainda nao ha fabrica; faltam ou sobram parametros; id nao e um inteiro positivo; posicao invalida ou "
        "fora da fabrica; nao ha engenheiro com esse numero ou maquina nessa posicao",
        "atribui 2 hr");
}
