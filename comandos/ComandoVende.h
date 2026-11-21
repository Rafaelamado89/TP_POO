#ifndef COMANDOVENDE_H
#define COMANDOVENDE_H

#include "Comando.h"

// vende <lc>: vende a maquina da posicao lc, recebendo uma percentagem do custo de compra (Settings)
class ComandoVende : public Comando {
public:
    ComandoVende();

    bool executa(Simulador& sim, std::istringstream& args) override;
    std::string getAjuda() const override;
};

#endif //COMANDOVENDE_H
