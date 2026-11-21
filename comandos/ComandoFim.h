#ifndef COMANDOFIM_H
#define COMANDOFIM_H

#include "Comando.h"

// fim: termina o programa (o Simulador liberta tudo ao ser destruido)
class ComandoFim : public Comando {
public:
    ComandoFim();

    bool precisaFabrica() const override;
    bool executa(Simulador& sim, std::istringstream& args) override;
    std::string getAjuda() const override;
};

#endif //COMANDOFIM_H
