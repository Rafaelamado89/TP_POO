#ifndef SOLO_H
#define SOLO_H

#include "Terreno.h"

// Posicao normal, onde pode ser colocada qualquer maquina.
class Solo : public Terreno {
public:
    char getCaracter() const override;
    std::string getDescricao() const override;
    Terreno* clona() const override;
};

#endif //SOLO_H
