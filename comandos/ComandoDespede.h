#ifndef COMANDODESPEDE_H
#define COMANDODESPEDE_H

#include "Comando.h"

// despede <id>: manda o engenheiro de volta para a Terra. Nesta versao so valida os parametros.
class ComandoDespede : public Comando {
public:
    ComandoDespede();

    bool executa(Simulador& sim, std::istringstream& args) override;
    std::string getAjuda() const override;
};

#endif //COMANDODESPEDE_H
