#ifndef COMANDOGRAVA_H
#define COMANDOGRAVA_H

#include "Comando.h"

// grava <nome>: guarda em memoria uma copia da fabrica. Nesta versao so valida os parametros.
class ComandoGrava : public Comando {
public:
    ComandoGrava();

    bool executa(Simulador& sim, std::istringstream& args) override;
    std::string getAjuda() const override;
};

#endif //COMANDOGRAVA_H
