#ifndef TRANSPORTADOR_H
#define TRANSPORTADOR_H

#include "Maquina.h"

class Transportador : public Maquina {
public:
    explicit Transportador(Direcao saida);
    ~Transportador();

    char getSimbolo() const override;
    bool recebe(Item* item) override;
    void atua(Maquina* destino, Terreno* terreno) override;
    std::string getDescricao() const override;

private:
    Item* item;
};

#endif //TRANSPORTADOR_H
