#ifndef COMANDOLPOSICAO_H
#define COMANDOLPOSICAO_H

#include "Comando.h"

// lposicao <lc> [n]: o terreno e a maquina da posicao lc (ou de todas as do quadrado de raio n a volta)
class ComandoLposicao : public Comando {
public:
    ComandoLposicao();

    bool executa(Simulador& sim, std::istringstream& args) override;
    std::string getAjuda() const override;
};

#endif //COMANDOLPOSICAO_H
