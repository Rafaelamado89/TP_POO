#ifndef COMANDOGRAVA_H
#define COMANDOGRAVA_H

#include "Comando.h"

class ComandoGrava : public Comando {
public:
    ComandoGrava();

    bool executa(Simulador& sim, std::istringstream& args) override;
    std::string getAjuda() const override;
};

#endif //COMANDOGRAVA_H
