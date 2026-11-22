#include "ComandoEstado.h"

#include <sstream>
#include "Fabrica.h"
#include "Simulador.h"

ComandoEstado::ComandoEstado() : Comando("estado", "estado") {
}

bool ComandoEstado::executa(Simulador& sim, std::istringstream& args) {
    if (!semMaisParametros(args)) {
        return erroSintaxe(sim);
    }
    sim.informa(sim.getFabrica().descricaoEstado());
    return true;
}

std::string ComandoEstado::getAjuda() const {
    return formataAjuda(
        "nenhum",
        "mostra o instante atual, os creditos, as maquinas (posicao, tipo, direcao, engenheiros e conteudo), "
        "os engenheiros e o total de itens de cada tipo enviados para a Terra desde o inicio",
        "ainda nao ha fabrica; parametros a mais",
        "estado");
}
