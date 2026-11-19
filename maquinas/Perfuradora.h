#ifndef PERFURADORA_H
#define PERFURADORA_H

#include "Maquina.h"

class Perfuradora : public Maquina {
public:
    explicit Perfuradora(Direcao saida);
    ~Perfuradora();

    bool recebe(Item* item) override;
    void atua(Maquina* destino, Terreno* terreno) override;
    bool melhora() override;
    std::string getDescricao() const override;

private:
    Item* item;               // materia-prima extraida por entregar (no maximo 1); nullptr se nao tiver
    int instantes;
    int probPerda;
};

#endif //PERFURADORA_H
