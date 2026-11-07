//
// Created by Rafael on 07/11/2026.
//

#ifndef KITHABITAT_H
#define KITHABITAT_H

#include "ProdutosRefinados.h"

class KitHabitat : public ProdutosRefinados {
  public:
    KitHabitat();
    Item* clona() const override;

};



#endif //KITHABITAT_H
