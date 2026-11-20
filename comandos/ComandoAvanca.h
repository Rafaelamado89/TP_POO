#ifndef COMANDOAVANCA_H
#define COMANDOAVANCA_H

#include "Comando.h"

// avanca [n]: avanca n instantes (1 por omissao), um de cada vez, mostrando o ecra no fim de cada um
class ComandoAvanca : public Comando {
public:
    ComandoAvanca();

    bool executa(Simulador& sim, std::istringstream& args) override;
    std::string getAjuda() const override;
};

#endif //COMANDOAVANCA_H
