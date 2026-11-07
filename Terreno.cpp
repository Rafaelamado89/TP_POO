#include "Terreno.h"
#include <stdexcept>

Terreno::Terreno() : tipo(Tipo::Solo), quantidade(0) {
}

Terreno::Terreno(Tipo t, int qtd) : tipo(t), quantidade(qtd) {

    if ((eDeposito() && quantidade < 1) || (!eDeposito() && quantidade !=0)) {
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