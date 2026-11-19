//
// Created by Rafael on 07/11/2026.
//

#ifndef AGUA_H
#define AGUA_H

#include "ProdutosRefinados.h"

class Agua : public ProdutosRefinados {
public:
    Agua();
    Item* clona() const override;

};



#endif //AGUA_H
