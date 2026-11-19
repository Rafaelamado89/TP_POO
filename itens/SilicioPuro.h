//
// Created by Rafael on 07/11/2026.
//

#ifndef SILICIOPURO_H
#define SILICIOPURO_H

#include "ProdutosRefinados.h"

class SilicioPuro : public ProdutosRefinados {
  public:
    SilicioPuro();
    Item* clona() const override;
};



#endif //SILICIOPURO_H
