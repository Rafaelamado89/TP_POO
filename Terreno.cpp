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
    return eDeposito(tipo);
}

bool Terreno::eDeposito(Tipo t) {
    return t == Tipo::Ferro || t == Tipo::Silicio || t == Tipo::Gelo;
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

bool Terreno::tipoDoMapa(char c, Tipo& resultado) {
    switch (c) {
        case '.':
            resultado = Tipo::Solo;
            return true;
        case '#':
            resultado = Tipo::Cratera;
            return true;
        case '%':
            resultado = Tipo::Ferro;
            return true;
        case '$':
            resultado = Tipo::Silicio;
            return true;
        case '~':
            resultado = Tipo::Gelo;
            return true;
        default:
            return false;
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
