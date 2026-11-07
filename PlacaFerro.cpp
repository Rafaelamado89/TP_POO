//
// Created by Rafael on 07/11/2026.
//

#include "PlacaFerro.h"
#include "Settings.h"

PlacaFerro::PlacaFerro() :
 ProdutosRefinados("Placa de Ferro", 'p', Settings::valor_placa_ferro) {}

Item* PlacaFerro::clona() const { return new PlacaFerro(*this);}