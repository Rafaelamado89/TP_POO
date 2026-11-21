#include "ComandoMelhora.h"

#include <sstream>
#include <string>
#include "Posicao.h"
#include "Settings.h"
#include "Simulador.h"

ComandoMelhora::ComandoMelhora() : Comando("melhora", "melhora <lc>") {
}

bool ComandoMelhora::executa(Simulador& sim, std::istringstream& args) {
    std::string txtPosicao;
    if (!(args >> txtPosicao) || !semMaisParametros(args)) {
        return erroSintaxe(sim);
    }
    Posicao p;
    if (!posicaoNaFabrica(sim, txtPosicao, p)) {
        return false;
    }
    sim.informa("melhora " + txtPosicao + ": parametros validos, mas este comando ainda nao tem efeito nesta versao");
    return true;
}

std::string ComandoMelhora::getAjuda() const {
    return formataAjuda(
        "<lc> a posicao da maquina, linha e coluna (ex.: hi)",
        "melhora a maquina dessa posicao, pagando o custo da melhoria: perfuradora (-" +
        std::to_string(Settings::perfuradora_melhoria_reducao_prob) + "% de perda, " +
        std::to_string(Settings::perfuradora_melhoria_custo) + " creditos), oficina (-" +
        std::to_string(Settings::oficina_melhoria_reducao_duracao) + " instante de producao, " +
        std::to_string(Settings::oficina_melhoria_custo) + " creditos), silo (-" +
        std::to_string(Settings::silo_melhoria_reducao_prob) + "% de perda, " +
        std::to_string(Settings::silo_melhoria_custo) + " creditos) ou lancador (-" +
        std::to_string(Settings::lancador_melhoria_reducao_prob) + "% de perda, " +
        std::to_string(Settings::lancador_melhoria_custo) + " creditos); se a maquina nao for melhoravel, nada "
        "acontece. Nesta versao so valida os parametros.",
        "ainda nao ha fabrica; falta a posicao ou ha parametros a mais; posicao invalida ou fora da fabrica",
        "melhora hi");
}
