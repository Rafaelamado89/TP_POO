#include "Deposito.h"
#include <stdexcept>
#include "Gelo.h"
#include "MinerioFerro.h"
#include "SilicioBruto.h"

Deposito::Deposito(char caracter, const std::string& nome, int quantidade)
    : caracter(caracter), nome(nome), quantidade(quantidade) {
    if (quantidade < 1) {
        throw std::invalid_argument("Deposito: quantidade invalida");
    }
}

char Deposito::getCaracter() const { return caracter; }

std::string Deposito::getDescricao() const {
    return "Deposito de " + nome + " (" + std::to_string(quantidade) +
           (quantidade == 1 ? " unidade)" : " unidades)");
}

Terreno* Deposito::clona() const { return new Deposito(*this); }

// Tira 1 unidade e devolve-a (quem chama fica dono); nullptr se ja estiver esgotado.
MateriaPrima* Deposito::extrai() {
    if (quantidade == 0) {
        return nullptr;
    }
    --quantidade;
    switch (caracter) {
        case '%':
            return new MinerioFerro();
        case '$':
            return new SilicioBruto();
        default:
            return new Gelo();
    }
}
