//
// Created by Rafael on 07/11/2026.
//

#include "MinerioFerro.h"
#include "PlacaFerro.h"
#include "Settings.h"

MinerioFerro::MinerioFerro() :
    MateriaPrima("Minerio de Ferro", 'f', Settings::valor_minerio_ferro) {}

Item* MinerioFerro::refina() const { return new PlacaFerro(); }
Item* MinerioFerro::clona() const { return new MinerioFerro(*this);}