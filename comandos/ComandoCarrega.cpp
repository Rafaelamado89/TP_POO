#include "ComandoCarrega.h"

#include <sstream>
#include <string>
#include "Fabrica.h"
#include "Simulador.h"

ComandoCarrega::ComandoCarrega() : Comando("carrega", "carrega <nome-do-ficheiro>") {
}

// E ele que cria a fabrica: corre sem ela (e recusa-se se ja existir)
bool ComandoCarrega::precisaFabrica() const {
    return false;
}

bool ComandoCarrega::executa(Simulador& sim, std::istringstream& args) {
    if (sim.temFabrica()) {
        sim.informa("A fabrica ja foi criada: fabrica e carrega so podem ser usados uma vez");
        return false;
    }

    std::string nomeFicheiro;
    if (!(args >> nomeFicheiro) || !semMaisParametros(args)) {
        return erroSintaxe(sim);
    }

    std::string erro;
    Fabrica* nova = Fabrica::carrega(nomeFicheiro, erro);   // nullptr se falhar: nesse caso nada foi criado
    if (nova == nullptr) {
        sim.informa("Nao foi possivel carregar '" + nomeFicheiro + "' (" + erro + "): a fabrica nao foi criada");
        return false;
    }
    sim.instalaFabrica(nova);
    sim.mostraEcra();
    return true;
}

std::string ComandoCarrega::getAjuda() const {
    return formataAjuda(
        "<nome-do-ficheiro> o ficheiro de texto com o mapa: na primeira linha, o numero de linhas e de colunas; "
        "depois, uma linha de texto por linha da fabrica, com . (solo), # (cratera), % (ferro), $ (silicio) "
        "e ~ (gelo)",
        "cria a fabrica a partir do mapa. Ele ou o fabrica tem de ser o primeiro comando executado com sucesso.",
        "a fabrica ja existe; falta o nome ou ha parametros a mais; o ficheiro nao existe ou nao respeita o "
        "formato (e nesse caso a fabrica nao e criada)",
        "carrega mapa1.txt");
}
