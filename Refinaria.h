#ifndef REFINARIA_H
#define REFINARIA_H

#include "Maquina.h"

// Aceita materias-primas (uma de cada vez, se estiver vazia), transforma-as em produtos refinados
// em N instantes e entrega o produto na direcao de saida.
// A planear: o item que tem dentro, instantes que faltam para acabar.
class Refinaria : public Maquina {
public:
    explicit Refinaria(Direcao saida);

    bool recebe(Item* item) override;
    void atua(Maquina* destino, Terreno* terreno) override;
    std::string getDescricao() const override;
};

#endif //REFINARIA_H
