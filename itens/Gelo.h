//
// Created by Rafael on 07/11/2026.
//

#ifndef GELO_H
#define GELO_H



#include "MateriaPrima.h"

class Gelo : public MateriaPrima {
public:
    Gelo();

    Item* refina() const override;
    Item* clona() const override;
};



#endif //GELO_H
