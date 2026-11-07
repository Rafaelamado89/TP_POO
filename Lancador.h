#ifndef LANCADOR_H
#define LANCADOR_H

#include "Maquina.h"

// Envia itens para a Terra, o que rende creditos. So lanca um item de N em N instantes e tem
// probabilidade de o perder, que pode ser melhorada. A direcao de saida e irrelevante.
// A planear: item por lancar, recarga, probabilidade de perda.
class Lancador : public Maquina {
public:
    explicit Lancador(Direcao saida);

    bool recebe(Item* item) override;
    void atua(Maquina* destino, Terreno* terreno) override;
    bool melhora() override;
    std::string getDescricao() const override;
};

#endif //LANCADOR_H
