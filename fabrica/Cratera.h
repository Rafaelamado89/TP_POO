#ifndef CRATERA_H
#define CRATERA_H

#include "Terreno.h"

class Cratera : public Terreno {
public:
    char getCaracter() const override;
    std::string getDescricao() const override;
    Terreno* clona() const override;
};

#endif //CRATERA_H
