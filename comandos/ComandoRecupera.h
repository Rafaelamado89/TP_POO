#ifndef COMANDORECUPERA_H
#define COMANDORECUPERA_H

#include "Comando.h"

class ComandoRecupera : public Comando {
public:
    ComandoRecupera();

    bool executa(Simulador& sim, std::istringstream& args) override;
    std::string getAjuda() const override;
};

#endif //COMANDORECUPERA_H
