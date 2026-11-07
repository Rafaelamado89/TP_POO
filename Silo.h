#ifndef SILO_H
#define SILO_H

#include "Maquina.h"

class Silo : public Maquina {
public:
    explicit Silo(Direcao saida);

    bool recebe(Item* item) override;
    void atua(Maquina* destino, Terreno* terreno) override;
    bool melhora() override;
    std::string getDescricao() const override;
};

#endif //SILO_H
