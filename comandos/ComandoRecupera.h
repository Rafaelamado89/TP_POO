#ifndef COMANDORECUPERA_H
#define COMANDORECUPERA_H

#include "Comando.h"

// recupera <nome>: volta a fabrica guardada com esse nome. Nesta versao so valida os parametros.
class ComandoRecupera : public Comando {
public:
    ComandoRecupera();

    bool executa(Simulador& sim, std::istringstream& args) override;
    std::string getAjuda() const override;
};

#endif //COMANDORECUPERA_H
