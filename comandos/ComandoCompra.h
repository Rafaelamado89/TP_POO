#ifndef COMANDOCOMPRA_H
#define COMANDOCOMPRA_H

#include "Comando.h"

class Maquina;

class ComandoCompra : public Comando {
public:
    ComandoCompra();

    bool executa(Simulador& sim, std::istringstream& args) override;
    std::string getAjuda() const override;

private:
    static bool tipoValido(const std::string& texto);
    static Maquina* criaMaquina(char tipo, Direcao saida);
};

#endif //COMANDOCOMPRA_H
