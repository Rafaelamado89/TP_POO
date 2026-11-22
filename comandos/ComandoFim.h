#ifndef COMANDOFIM_H
#define COMANDOFIM_H

#include "Comando.h"

class ComandoFim : public Comando {
public:
    ComandoFim();

    bool precisaFabrica() const override;
    bool executa(Simulador& sim, std::istringstream& args) override;
    std::string getAjuda() const override;
};

#endif //COMANDOFIM_H
