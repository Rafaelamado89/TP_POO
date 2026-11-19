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
    Item* item;               // item por lancar; nullptr se nao tiver
    int instantesRestantes;   // instantes que faltam para poder lancar de novo
    int probPerda;            // probabilidade (%) de o item se perder no lancamento
};

#endif //LANCADOR_H
