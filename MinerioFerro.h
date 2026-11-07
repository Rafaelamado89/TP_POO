//
// Created by Rafael on 07/11/2026.
//

#ifndef MINERIOFERRO_H
#define MINERIOFERRO_H

#include "MateriaPrima.h"

class MinerioFerro : public MateriaPrima {
  public:
    MinerioFerro();

    Item* refina() const override;
    Item* clona() const override;
};



#endif //MINERIOFERRO_H
