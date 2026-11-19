//
// Created by Rafael on 07/11/2026.
//

#ifndef PLACAFERRO_H
#define PLACAFERRO_H

#include "ProdutosRefinados.h"

class PlacaFerro : public ProdutosRefinados {
public:
    PlacaFerro();
    Item* clona() const override;

};



#endif //PLACAFERRO_H
