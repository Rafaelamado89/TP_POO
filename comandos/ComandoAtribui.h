#ifndef COMANDOATRIBUI_H
#define COMANDOATRIBUI_H

#include "Comando.h"

// atribui <id> <lc>: associa um engenheiro a maquina da posicao lc. Nesta versao so valida os parametros.
class ComandoAtribui : public Comando {
public:
    ComandoAtribui();

    bool executa(Simulador& sim, std::istringstream& args) override;
    std::string getAjuda() const override;
};

#endif //COMANDOATRIBUI_H
