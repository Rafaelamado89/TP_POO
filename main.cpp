#include <exception>
#include <iostream>
#include "Simulador.h"

int main() {
    try {
        Simulador simulador;   // cria os comandos; a fabrica so com o fabrica ou o carrega
        simulador.corre();     // ate ao comando fim (ou ao fim da entrada)
    } catch (const std::exception& e) {
        // Os erros esperados e os de cada comando sao tratados la dentro; isto e para nada ficar por tratar
        std::cerr << "Erro inesperado: " << e.what() << '\n';
        return 1;
    }
    // Ao sair do bloco, o destrutor do Simulador ja libertou a fabrica e os comandos: saida limpa
    return 0;
}
