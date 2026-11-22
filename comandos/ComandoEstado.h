#ifndef COMANDOESTADO_H
#define COMANDOESTADO_H

#include "Comando.h"

class ComandoEstado : public Comando {
public:
    ComandoEstado();

    bool executa(Simulador& sim, std::istringstream& args) override;
    std::string getAjuda() const override;
};

#endif //COMANDOESTADO_H
