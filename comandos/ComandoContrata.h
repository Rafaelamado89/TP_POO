#ifndef COMANDOCONTRATA_H
#define COMANDOCONTRATA_H

#include "Comando.h"

class ComandoContrata : public Comando {
public:
    ComandoContrata();

    bool executa(Simulador& sim, std::istringstream& args) override;
    std::string getAjuda() const override;
};

#endif //COMANDOCONTRATA_H
