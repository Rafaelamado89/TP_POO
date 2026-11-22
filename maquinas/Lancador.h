#ifndef LANCADOR_H
#define LANCADOR_H

#include "Maquina.h"

class Lancador : public Maquina {
public:
    explicit Lancador(Direcao saida);
    ~Lancador();

    bool recebe(Item* item) override;
    void atua(Maquina* destino, Terreno* terreno) override;
    bool melhora() override;
    std::string getDescricao() const override;

private:
    Item* item;
    int instantesRestantes;
    int probPerda;
};

#endif //LANCADOR_H
