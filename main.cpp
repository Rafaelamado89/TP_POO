#include <exception>
#include <iostream>
#include "Simulador.h"

int main() {
    try {
        Simulador simulador;
        simulador.corre();
    } catch (const std::exception& e) {
        std::cerr << "Erro inesperado: " << e.what() << '\n';
        return 1;
    }
    // Ao sair do bloco, o destrutor do Simulador ja libertou a fabrica e os comandos: saida limpa
    return 0;
}
