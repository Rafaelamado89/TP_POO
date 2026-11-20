#include "ComandoCompra.h"

#include <sstream>
#include <string>
#include "Fabrica.h"
#include "Lancador.h"
#include "Oficina.h"
#include "Perfuradora.h"
#include "Posicao.h"
#include "Refinaria.h"
#include "Settings.h"
#include "Silo.h"
#include "Simulador.h"
#include "Transportador.h"

ComandoCompra::ComandoCompra() : Comando("compra", "compra <tipo> <lc> <dir>") {
}

bool ComandoCompra::executa(Simulador& sim, std::istringstream& args) {
    std::string txtTipo, txtPosicao, txtDirecao;
    if (!(args >> txtTipo >> txtPosicao >> txtDirecao) || !semMaisParametros(args)) {
        return erroSintaxe(sim);
    }
    if (!tipoValido(txtTipo)) {
        sim.informa("Tipo de maquina invalido: '" + txtTipo + "' (p, t, r, o, s ou l)");
        return false;
    }
    Posicao p;
    if (!posicaoNaFabrica(sim, txtPosicao, p)) {
        return false;
    }
    Direcao saida = Direita;
    if (!paraDirecao(txtDirecao, saida)) {
        sim.informa("Direcao invalida: '" + txtDirecao + "' (c, b, e ou d)");
        return false;
    }

    // Quem decide se a compra pode ser feita (cratera, ocupada, creditos) e a fabrica
    std::string erro;
    if (!sim.getFabrica().compra(criaMaquina(txtTipo[0], saida), p, erro)) {
        sim.informa("Nao foi possivel comprar: " + erro);
        return false;
    }
    sim.mostraEcra();
    return true;
}

bool ComandoCompra::tipoValido(const std::string& texto) {
    return texto == "p" || texto == "t" || texto == "r" || texto == "o" || texto == "s" || texto == "l";
}

Maquina* ComandoCompra::criaMaquina(char tipo, Direcao saida) {
    switch (tipo) {
        case 'p':
            return new Perfuradora(saida);
        case 't':
            return new Transportador(saida);
        case 'r':
            return new Refinaria(saida);
        case 'o':
            return new Oficina(saida);
        case 's':
            return new Silo(saida);
        case 'l':
            return new Lancador(saida);
        default:
            return nullptr;
    }
}

std::string ComandoCompra::getAjuda() const {
    return formataAjuda(
        "<tipo> p (perfuradora, " + std::to_string(Settings::perfuradora_custo) + " creditos), t (transportador, " +
        std::to_string(Settings::transportador_custo) + "), r (refinaria, " +
        std::to_string(Settings::refinaria_custo) + "), o (oficina, " + std::to_string(Settings::oficina_custo) +
        "), s (silo, " + std::to_string(Settings::silo_custo) + ") ou l (lancador, " +
        std::to_string(Settings::lancador_custo) + "); <lc> a posicao, linha e coluna (ex.: ce); "
        "<dir> a direcao de saida: c (cima), b (baixo), e (esquerda) ou d (direita)",
        "compra a maquina, desconta o custo nos creditos e coloca-a na posicao, a entregar na direcao indicada",
        "ainda nao ha fabrica; faltam ou sobram parametros; tipo, posicao ou direcao invalidos; a posicao fica "
        "fora da fabrica, e uma cratera ou ja tem uma maquina; os creditos nao chegam",
        "compra t ce d");
}
