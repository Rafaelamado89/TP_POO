#include "ComandoFim.h"

#include <sstream>
#include "Simulador.h"

ComandoFim::ComandoFim() : Comando("fim", "fim") {
}

bool ComandoFim::precisaFabrica() const {
    return false;
}

// So para o ciclo. A memoria e libertada quando o Simulador e destruido, no fim do main: o destrutor dele
// apaga a fabrica (que apaga os terrenos e as maquinas, e estas os seus itens) e os comandos.
bool ComandoFim::executa(Simulador& sim, std::istringstream& args) {
    if (!semMaisParametros(args)) {
        return erroSintaxe(sim);
    }
    sim.informa("Fim da simulacao.");
    sim.termina();
    return true;
}

std::string ComandoFim::getAjuda() const {
    return formataAjuda(
        "nenhum",
        "termina o programa, libertando toda a memoria (a fabrica, as maquinas, os itens e os comandos)",
        "parametros a mais",
        "fim");
}
