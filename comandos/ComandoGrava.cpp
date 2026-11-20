#include "ComandoGrava.h"

#include <sstream>
#include <string>
#include "Simulador.h"

ComandoGrava::ComandoGrava() : Comando("grava", "grava <nome>") {
}

bool ComandoGrava::executa(Simulador& sim, std::istringstream& args) {
    std::string nome;
    if (!(args >> nome) || !semMaisParametros(args)) {
        return erroSintaxe(sim);
    }
    sim.informa("grava " + nome + ": parametros validos, mas este comando ainda nao tem efeito nesta versao");
    return true;
}

std::string ComandoGrava::getAjuda() const {
    return formataAjuda(
        "<nome> o nome da copia (uma palavra)",
        "guarda em memoria uma copia da fabrica e de tudo o que nela esta (terreno, maquinas e itens, creditos, "
        "instante e engenheiros, sem a associacao a maquinas); se ja houver uma copia com esse nome, e "
        "substituida. Nesta versao so valida os parametros.",
        "ainda nao ha fabrica; falta o nome ou ha parametros a mais",
        "grava antes");
}
