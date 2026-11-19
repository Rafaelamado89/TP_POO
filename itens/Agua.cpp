//
// Created by Rafael on 07/11/2026.
//

#include "Agua.h"
#include "Settings.h"

Agua::Agua() :
 ProdutosRefinados("Agua", 'a', Settings::valor_agua) {}

Item* Agua::clona() const { return new Agua(*this);}