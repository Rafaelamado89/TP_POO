#ifndef SILO_H
#define SILO_H

#include "Maquina.h"

class Silo : public Maquina {
public:
    explicit Silo(Direcao saida);
    ~Silo();

    bool recebe(Item* item) override;
    void atua(Maquina* destino, Terreno* terreno) override;
    bool melhora() override;
    std::string getDescricao() const override;

private:
    Item* retiraMaisAntigo();   // tira o item mais antigo do array (nao o apaga: devolve-o)

    Item** itens;   // array dinamico com exatamente numItens ponteiros; itens[0] e o mais antigo
    int numItens;
    int probPerda;
};

#endif //SILO_H
