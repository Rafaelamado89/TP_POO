#ifndef COMANDOCARREGA_H
#define COMANDOCARREGA_H

#include "Comando.h"

// carrega <nome-do-ficheiro>: cria a fabrica a partir do mapa descrito num ficheiro de texto
class ComandoCarrega : public Comando {
public:
    ComandoCarrega();

    bool precisaFabrica() const override;
    bool executa(Simulador& sim, std::istringstream& args) override;
    std::string getAjuda() const override;
};

#endif //COMANDOCARREGA_H
