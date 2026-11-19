//
// Created by Rafael on 07/11/2026.
//

#ifndef MATERIAPRIMA_H
#define MATERIAPRIMA_H

#include "Item.h"

class MateriaPrima : public Item {
  public:
    MateriaPrima(const std::string& nome, char simbolo, int valor) :
            Item(nome, simbolo, valor) {}

    virtual Item* refina() const = 0;
};

#endif //MATERIAPRIMA_H