//
// Created by Rafael on 07/11/2026.
//

#include "SilicioPuro.h"
#include "Settings.h"

SilicioPuro::SilicioPuro() :
 ProdutosRefinados("Silicio Puro", 'i', Settings::valor_silicio_puro) {}

Item* SilicioPuro::clona() const { return new SilicioPuro(*this);}
