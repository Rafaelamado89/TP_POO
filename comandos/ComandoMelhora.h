#ifndef COMANDOMELHORA_H
#define COMANDOMELHORA_H

#include "Comando.h"

// melhora <lc>: melhora a maquina da posicao lc. Nesta versao so valida os parametros.
class ComandoMelhora : public Comando {
public:
    ComandoMelhora();

    bool executa(Simulador& sim, std::istringstream& args) override;
    std::string getAjuda() const override;
};

#endif //COMANDOMELHORA_H
