//
// Created by Luis Vieira on 07/11/2026.
//

#include "Terreno.h"
#include <stdexcept>
#include <string>

Terreno::Terreno() : tipo(Tipo::Solo), quantidade(0) {
}

Terreno::Terreno(Tipo t, int qtd) : tipo(t), quantidade(qtd) {
    if ((eDeposito() && quantidade < 1) || (!eDeposito() && quantidade != 0)) {
        throw std::invalid_argument("Terreno: quantidade invalida para o tipo");
    }
}

bool Terreno::eDeposito() const {
    return tipo == Tipo::Ferro || tipo == Tipo::Silicio || tipo == Tipo::Gelo;
}

char Terreno::getCaracter() const {
    switch (tipo) {
        case Tipo::Solo:
            return ' ';
        case Tipo::Cratera:
            return '#';
        case Tipo::Ferro:
            return '%';
        case Tipo::Silicio:
            return '$';
        case Tipo::Gelo:
            return '~';
    }
    return '?';
}

Terreno::Tipo Terreno::tipoDoMapa(char c) {
    switch (c) {
        case '.':
            return Tipo::Solo;
        case '#':
            return Tipo::Cratera;
        case '%':
            return Tipo::Ferro;
        case '$':
            return Tipo::Silicio;
        case '~':
            return Tipo::Gelo;
        default:
            throw std::invalid_argument(std::string("Mapa: caracter invalido '") + c +
                                        "' (codigo " + std::to_string(static_cast<int>(c)) + ")");
    }
}

std::string Terreno::getDescricao() const {
    switch (tipo) {
        case Tipo::Solo:
            return "Solo";
        case Tipo::Cratera:
            return "Cratera";
        case Tipo::Ferro:
            return "Deposito de ferro (" + std::to_string(quantidade) +
                   (quantidade == 1 ? " unidade)" : " unidades)");
        case Tipo::Silicio:
            return "Deposito de silicio (" + std::to_string(quantidade) +
                   (quantidade == 1 ? " unidade)" : " unidades)");
        case Tipo::Gelo:
            return "Deposito de gelo (" + std::to_string(quantidade) +
                   (quantidade == 1 ? " unidade)" : " unidades)");
    }
    return "Desconhecido";
}
