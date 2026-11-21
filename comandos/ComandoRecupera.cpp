#include "ComandoRecupera.h"

#include <sstream>
#include <string>
#include "Simulador.h"

ComandoRecupera::ComandoRecupera() : Comando("recupera", "recupera <nome>") {
}

bool ComandoRecupera::executa(Simulador& sim, std::istringstream& args) {
    std::string nome;
    if (!(args >> nome) || !semMaisParametros(args)) {
        return erroSintaxe(sim);
    }
    sim.informa("recupera " + nome + ": parametros validos, mas este comando ainda nao tem efeito nesta versao");
    return true;
}

std::string ComandoRecupera::getAjuda() const {
    return formataAjuda(
        "<nome> o nome da copia (uma palavra)",
        "a fabrica volta a ser como era quando a copia com esse nome foi feita; os engenheiros voltam, mas "
        "livres; a copia nao e apagada. Nesta versao so valida os parametros.",
        "ainda nao ha fabrica; falta o nome ou ha parametros a mais; nao ha nenhuma copia com esse nome",
        "recupera antes");
}
