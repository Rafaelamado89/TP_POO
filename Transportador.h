#ifndef TRANSPORTADOR_H
#define TRANSPORTADOR_H

#include "Maquina.h"

// Transporta 1 item de cada vez (de qualquer tipo, desde que esteja vazio) para a direcao de saida.
// Vazio, desenha-se como a seta da direcao; com um item, como o caracter do item.
// A planear: o item que transporta.
class Transportador : public Maquina {
public:
    explicit Transportador(Direcao saida);

    bool recebe(Item* item) override;
    void atua(Maquina* destino, Terreno* terreno) override;
    std::string getDescricao() const override;
};

#endif //TRANSPORTADOR_H
