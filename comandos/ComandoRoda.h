#ifndef COMANDORODA_H
#define COMANDORODA_H

#include "Comando.h"

class ComandoRoda : public Comando {
public:
    ComandoRoda();

    bool executa(Simulador& sim, std::istringstream& args) override;
    std::string getAjuda() const override;
};

#endif //COMANDORODA_H
