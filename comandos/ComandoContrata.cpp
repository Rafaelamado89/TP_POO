#include "ComandoContrata.h"

#include <sstream>
#include <string>
#include "Settings.h"
#include "Simulador.h"

ComandoContrata::ComandoContrata() : Comando("contrata", "contrata <nome>") {
}

bool ComandoContrata::executa(Simulador& sim, std::istringstream& args) {
    std::string nome;
    if (!(args >> nome) || !semMaisParametros(args)) {
        return erroSintaxe(sim);
    }
    sim.informa("contrata " + nome + ": parametros validos, mas este comando ainda nao tem efeito nesta versao");
    return true;
}

std::string ComandoContrata::getAjuda() const {
    return formataAjuda(
        "<nome> o nome do engenheiro (uma palavra; pode repetir-se, porque o numero de cada um e unico)",
        "contrata um engenheiro, que fica livre, pagando " + std::to_string(Settings::engenheiro_custo_contratacao) +
        " creditos; depois recebe " + std::to_string(Settings::engenheiro_salario) + " credito(s) de salario por "
        "instante. Nesta versao so valida os parametros.",
        "ainda nao ha fabrica; falta o nome ou ha parametros a mais; os creditos nao chegam",
        "contrata joaquim");
}
