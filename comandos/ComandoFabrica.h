#ifndef COMANDOFABRICA_H
#define COMANDOFABRICA_H

#include "Comando.h"

class ComandoFabrica : public Comando {
public:
    ComandoFabrica();

    bool precisaFabrica() const override;
    bool executa(Simulador& sim, std::istringstream& args) override;
    std::string getAjuda() const override;
};

#endif //COMANDOFABRICA_H
