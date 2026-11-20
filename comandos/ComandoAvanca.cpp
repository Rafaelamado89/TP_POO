#include "ComandoAvanca.h"

#include <sstream>
#include <string>
#include "Fabrica.h"
#include "Simulador.h"

ComandoAvanca::ComandoAvanca() : Comando("avanca", "avanca [n]") {
}

bool ComandoAvanca::executa(Simulador& sim, std::istringstream& args) {
    int n = 1;   // sem parametro, avanca 1
    std::string txtN;
    if (args >> txtN) {
        if (!semMaisParametros(args)) {
            return erroSintaxe(sim);
        }
        if (!paraInteiro(txtN, n) || n < 1) {
            sim.informa("O numero de instantes tem de ser um inteiro positivo (ex.: avanca 10)");
            return false;
        }
    }

    // Um instante de cada vez, e o ecra no fim de cada um
    Fabrica& fab = sim.getFabrica();
    for (int i = 0; i < n; ++i) {
        fab.avancaInstante();
        sim.mostraEcra();
    }
    return true;
}

std::string ComandoAvanca::getAjuda() const {
    return formataAjuda(
        "[n] numero de instantes a avancar (inteiro positivo; se nao for indicado, avanca 1)",
        "avanca n instantes, um de cada vez: em cada instante as maquinas atuam e fazem-se as contas aos custos "
        "e ganhos; o ecra e mostrado no fim de cada instante",
        "ainda nao ha fabrica; n nao e um inteiro positivo; parametros a mais",
        "avanca 10");
}
