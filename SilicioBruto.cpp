//
// Created by Rafael on 07/11/2026.
//

#include "SilicioBruto.h"
#include "SilicioPuro.h"
#include "Settings.h"

SilicioBruto::SilicioBruto() :
    MateriaPrima("Silicio Bruto", 's', Settings::valor_silicio_bruto) {}

Item* SilicioBruto::refina() const { return new SilicioPuro(); }
Item* SilicioBruto::clona() const { return new SilicioBruto(*this);}
