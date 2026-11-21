#include "ComandoVende.h"

#include <sstream>
#include <string>
#include "Fabrica.h"
#include "Maquina.h"
#include "Posicao.h"
#include "Settings.h"
#include "Simulador.h"

ComandoVende::ComandoVende() : Comando("vende", "vende <lc>") {
}

bool ComandoVende::executa(Simulador& sim, std::istringstream& args) {
    std::string txtPosicao;
    if (!(args >> txtPosicao) || !semMaisParametros(args)) {
        return erroSintaxe(sim);
    }
    Posicao p;
    if (!posicaoNaFabrica(sim, txtPosicao, p)) {
        return false;
    }

    Fabrica& fab = sim.getFabrica();
    Maquina* m = fab.getMaquina(p);
    if (m == nullptr) {
        sim.informa("Nao ha nenhuma maquina na posicao " + txtPosicao);
        return false;
    }

    // A fabrica recebe a percentagem do custo de compra definida na Settings; os itens da maquina perdem-se
    int ganho = m->getCusto() * Settings::maquina_percentagem_venda / 100;
    fab.removeMaquina(p);
    fab.recebeCreditos(ganho);
    sim.informa("Maquina vendida por " + std::to_string(ganho) + " creditos");
    sim.mostraEcra();
    return true;
}

std::string ComandoVende::getAjuda() const {
    return formataAjuda(
        "<lc> a posicao da maquina, linha e coluna (ex.: ce)",
        "vende a maquina dessa posicao: a fabrica recebe " + std::to_string(Settings::maquina_percentagem_venda) +
        "% do custo de compra e os itens que a maquina tiver perdem-se",
        "ainda nao ha fabrica; falta a posicao ou ha parametros a mais; posicao invalida ou fora da fabrica; "
        "nao ha maquina nessa posicao",
        "vende ce");
}
