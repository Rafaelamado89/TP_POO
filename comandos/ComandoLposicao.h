#ifndef COMANDOLPOSICAO_H
#define COMANDOLPOSICAO_H

#include "Comando.h"

class ComandoLposicao : public Comando {
public:
    ComandoLposicao();

    bool executa(Simulador& sim, std::istringstream& args) override;
    std::string getAjuda() const override;
};

#endif //COMANDOLPOSICAO_H
