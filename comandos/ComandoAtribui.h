#ifndef COMANDOATRIBUI_H
#define COMANDOATRIBUI_H

#include "Comando.h"

class ComandoAtribui : public Comando {
public:
    ComandoAtribui();

    bool executa(Simulador& sim, std::istringstream& args) override;
    std::string getAjuda() const override;
};

#endif //COMANDOATRIBUI_H
