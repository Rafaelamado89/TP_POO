#ifndef COMANDOMELHORA_H
#define COMANDOMELHORA_H

#include "Comando.h"

class ComandoMelhora : public Comando {
public:
    ComandoMelhora();

    bool executa(Simulador& sim, std::istringstream& args) override;
    std::string getAjuda() const override;
};

#endif //COMANDOMELHORA_H
