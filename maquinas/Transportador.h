#ifndef TRANSPORTADOR_H
#define TRANSPORTADOR_H

#include "Maquina.h"

class Transportador : public Maquina {
public:
    explicit Transportador(Direcao saida);
    ~Transportador();


    bool recebe(Item* item) override;
    void atua(Maquina* destino, Terreno* terreno) override;
    std::string getDescricao() const override;

private:
    Item* item;               // item que transporta; nullptr se estiver vazio
};

#endif //TRANSPORTADOR_H
