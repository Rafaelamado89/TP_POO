#ifndef OFICINA_H
#define OFICINA_H

#include "Maquina.h"

// Produz kits de habitat a partir de uma receita fixa (placas de ferro, silicio puro e agua).
// Tem melhoria que reduz a duracao da producao.
// A planear: ingredientes ja recebidos, kit produzido por entregar, instantes que faltam.
class Oficina : public Maquina {
public:
    explicit Oficina(Direcao saida);

    bool recebe(Item* item) override;
    void atua(Maquina* destino, Terreno* terreno) override;
    bool melhora() override;
    std::string getDescricao() const override;
};

#endif //OFICINA_H
