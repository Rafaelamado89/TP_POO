#ifndef PERFURADORA_H
#define PERFURADORA_H

#include "Maquina.h"

// Extrai materia-prima do deposito onde esta (1 unidade a cada N instantes), com probabilidade de
// perda que pode ser melhorada. Guarda no maximo 1 item por entregar. Nao aceita itens de outras maquinas.
// A planear: probabilidade de perda, item por entregar, contagem dos instantes.
class Perfuradora : public Maquina {
public:
    explicit Perfuradora(Direcao saida);

    bool recebe(Item* item) override;
    void atua(Maquina* destino, Terreno* terreno) override;
    bool melhora() override;
    std::string getDescricao() const override;
};

#endif //PERFURADORA_H
