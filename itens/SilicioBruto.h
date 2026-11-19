//
// Created by Rafael on 07/11/2026.
//

#ifndef SILICIOBRUTO_H
#define SILICIOBRUTO_H



#include "MateriaPrima.h"

class SilicioBruto : public MateriaPrima {
public:
    SilicioBruto();

    Item* refina() const override;
    Item* clona() const override;
};



#endif //SILICIOBRUTO_H
