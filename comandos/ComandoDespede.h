#ifndef COMANDODESPEDE_H
#define COMANDODESPEDE_H

#include "Comando.h"

class ComandoDespede : public Comando {
public:
    ComandoDespede();

    bool executa(Simulador& sim, std::istringstream& args) override;
    std::string getAjuda() const override;
};

#endif //COMANDODESPEDE_H
