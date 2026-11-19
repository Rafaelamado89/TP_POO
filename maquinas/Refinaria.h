#ifndef REFINARIA_H
#define REFINARIA_H

#include "Maquina.h"

class Refinaria : public Maquina {
public:
    explicit Refinaria(Direcao saida);
    ~Refinaria();

    bool recebe(Item* item) override;
    void atua(Maquina* destino, Terreno* terreno) override;
    std::string getDescricao() const override;

private:
    Item* item;               // materia-prima a transformar ou produto por entregar; nullptr se estiver vazia
    int instantesRestantes;
};

#endif //REFINARIA_H
