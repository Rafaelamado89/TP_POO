//
// Created by Rafael on 07/11/2026.
//

#include "KitHabitat.h"
#include "Settings.h"

KitHabitat::KitHabitat() :
 ProdutosRefinados("Kit de Habitat", 'k', Settings::valor_kit_habitat) {}

Item* KitHabitat::clona() const { return new KitHabitat(*this);}