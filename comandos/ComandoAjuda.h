#ifndef COMANDOAJUDA_H
#define COMANDOAJUDA_H

#include "Comando.h"

class ComandoAjuda : public Comando {
public:
    ComandoAjuda();

    bool precisaFabrica() const override;
    bool executa(Simulador& sim, std::istringstream& args) override;
    std::string getAjuda() const override;
};

#endif //COMANDOAJUDA_H
