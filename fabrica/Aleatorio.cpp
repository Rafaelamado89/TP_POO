//
// Created by Luis Vieira on 07/11/2026.
//

#include "Aleatorio.h"

#include <stdexcept>
#include <string>

std::mt19937 &Aleatorio::gerador() {
    static std::mt19937 g(std::random_device{}());
    return g;
}

int Aleatorio::entre(int min, int max) {
    if (min > max) {
        throw std::invalid_argument("Aleatorio: intervalo invalido");
    }
    std::uniform_int_distribution<int> d(min, max);
    return d(gerador());
}
