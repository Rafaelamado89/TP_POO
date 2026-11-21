#ifndef COMANDOESTADO_H
#define COMANDOESTADO_H

#include "Comando.h"

// estado: o instante, os creditos, as maquinas, os engenheiros e o total enviado de cada tipo
class ComandoEstado : public Comando {
public:
    ComandoEstado();

    bool executa(Simulador& sim, std::istringstream& args) override;
    std::string getAjuda() const override;
};

#endif //COMANDOESTADO_H
