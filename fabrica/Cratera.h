#ifndef CRATERA_H
#define CRATERA_H

#include "Terreno.h"

// Posicao onde nao pode ser colocado nada.
class Cratera : public Terreno {
public:
    char getCaracter() const override;
    std::string getDescricao() const override;
    Terreno* clona() const override;
};

#endif //CRATERA_H
