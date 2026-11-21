#ifndef COMANDORODA_H
#define COMANDORODA_H

#include "Comando.h"

// roda <lc> <dir>: muda a direcao de saida da maquina da posicao lc
class ComandoRoda : public Comando {
public:
    ComandoRoda();

    bool executa(Simulador& sim, std::istringstream& args) override;
    std::string getAjuda() const override;
};

#endif //COMANDORODA_H
