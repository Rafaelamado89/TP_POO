#ifndef DEPOSITO_H
#define DEPOSITO_H

#include <string>
#include "Terreno.h"

// Posicao com uma quantidade finita de uma materia-prima (ferro, silicio ou gelo).
class Deposito : public Terreno {
public:

    Deposito(char caracter, const std::string& nome, int quantidade);

    char getCaracter() const override;
    std::string getDescricao() const override;
    Terreno* clona() const override;

private:
    char caracter;
    std::string nome;
    int quantidade;
};

#endif //DEPOSITO_H
