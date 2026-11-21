#include "ComandoDespede.h"

#include <sstream>
#include <string>
#include "Simulador.h"

ComandoDespede::ComandoDespede() : Comando("despede", "despede <id>") {
}

bool ComandoDespede::executa(Simulador& sim, std::istringstream& args) {
    std::string txtId;
    if (!(args >> txtId) || !semMaisParametros(args)) {
        return erroSintaxe(sim);
    }
    int id = 0;
    if (!paraInteiro(txtId, id) || id < 1) {
        sim.informa("O numero do engenheiro tem de ser um inteiro positivo (ex.: despede 2)");
        return false;
    }
    sim.informa("despede " + txtId + ": parametros validos, mas este comando ainda nao tem efeito nesta versao");
    return true;
}

std::string ComandoDespede::getAjuda() const {
    return formataAjuda(
        "<id> o numero do engenheiro (inteiro positivo)",
        "envia o engenheiro em ferias permanentes para a Terra: deixa de fazer parte da fabrica e de receber "
        "salario. Nesta versao so valida os parametros.",
        "ainda nao ha fabrica; falta o numero ou ha parametros a mais; id nao e um inteiro positivo; nao ha "
        "engenheiro com esse numero",
        "despede 2");
}
