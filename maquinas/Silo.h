#ifndef SILO_H
#define SILO_H

#include "Maquina.h"

class Silo : public Maquina {
public:
    explicit Silo(Direcao saida);
    ~Silo();

    bool recebe(Item* item) override;
    void atua(Maquina* destino, Terreno* terreno) override;
    void fimInstante() override;
    bool melhora() override;
    std::string getDescricao() const override;

private:
    Item* retiraMaisAntigo();

    Item** itens;   // array dinamico com exatamente numItens ponteiros; itens[0] e o mais antigo
    int numItens;
    int novos;      // quantos chegaram neste instante: so saem a partir do seguinte
    int probPerda;
};

#endif //SILO_H
