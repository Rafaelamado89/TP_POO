#include "Solo.h"

char Solo::getCaracter() const { return ' '; }
std::string Solo::getDescricao() const { return "Solo"; }
Terreno* Solo::clona() const { return new Solo(*this); }
