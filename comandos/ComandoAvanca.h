#ifndef COMANDOAVANCA_H
#define COMANDOAVANCA_H

#include "Comando.h"

class ComandoAvanca : public Comando {
public:
    ComandoAvanca();

    bool executa(Simulador& sim, std::istringstream& args) override;
    std::string getAjuda() const override;
};

#endif //COMANDOAVANCA_H
