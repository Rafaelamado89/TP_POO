#include "Refinaria.h"
#include "Settings.h"

Refinaria::Refinaria(Direcao saida) : Maquina('R', Settings::refinaria_custo, saida) {}


bool Refinaria::recebe(Item*) { return false; }
void Refinaria::atua(Maquina*, Terreno*) {}
std::string Refinaria::getDescricao() const { return ""; }
