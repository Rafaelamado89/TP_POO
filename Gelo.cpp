//
// Created by Rafael on 07/11/2026.
//

#include "Gelo.h"
#include "Agua.h"
#include "Settings.h"

Gelo::Gelo() :
    MateriaPrima("Gelo", 'g', Settings::valor_gelo) {}

Item* Gelo::refina() const { return new Agua(); }
Item* Gelo::clona() const { return new Gelo(*this);}