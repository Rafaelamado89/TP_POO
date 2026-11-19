#include "Deposito.h"
#include <stdexcept>

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


MateriaPrima* Deposito::extrai() { return nullptr; }
