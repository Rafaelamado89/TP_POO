#ifndef COMANDOAJUDA_H
#define COMANDOAJUDA_H

#include "Comando.h"

// ajuda [comando]: a lista dos comandos (sintaxe resumida) ou a ajuda detalhada de um deles
class ComandoAjuda : public Comando {
public:
    ComandoAjuda();

    bool precisaFabrica() const override;
    bool executa(Simulador& sim, std::istringstream& args) override;
    std::string getAjuda() const override;
};

#endif //COMANDOAJUDA_H
