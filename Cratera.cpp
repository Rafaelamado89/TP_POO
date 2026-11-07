#include "Cratera.h"

char Cratera::getCaracter() const { return '#'; }
std::string Cratera::getDescricao() const { return "Cratera"; }
Terreno* Cratera::clona() const { return new Cratera(*this); }
