#include "ComandoAjuda.h"

#include <sstream>
#include <string>
#include "Simulador.h"

ComandoAjuda::ComandoAjuda() : Comando("ajuda", "ajuda [comando]") {
}

bool ComandoAjuda::precisaFabrica() const {
    return false;
}

bool ComandoAjuda::executa(Simulador& sim, std::istringstream& args) {
    std::string nome;

    if (!(args >> nome)) {
        std::ostringstream lista;
        lista << "Comandos:";
        for (int i = 0; i < sim.getNumComandos(); ++i) {
            lista << "\n  " << sim.getComando(i)->getSintaxe();
        }
        lista << "\nPara a ajuda detalhada de um comando: ajuda <comando> (ex.: ajuda compra)";
        sim.informa(lista.str());
        return true;
    }

    if (!semMaisParametros(args)) {
        return erroSintaxe(sim);
    }
    const Comando* comando = sim.procuraComando(nome);
    if (comando == nullptr) {
        sim.informa("Nao existe o comando '" + nome + "' (ajuda, sem parametro, mostra a lista)");
        return false;
    }
    sim.informa(comando->getAjuda());
    return true;
}

std::string ComandoAjuda::getAjuda() const {
    return formataAjuda(
        "[comando] o nome de um comando (opcional)",
        "sem parametro, mostra a lista de todos os comandos, um por linha, com a sintaxe resumida; com o nome "
        "de um comando, mostra a ajuda detalhada desse comando",
        "o comando indicado nao existe; parametros a mais",
        "ajuda compra");
}
