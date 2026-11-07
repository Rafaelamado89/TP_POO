#include "Silo.h"
#include "Settings.h"

Silo::Silo(Direcao saida) : Maquina('S', Settings::silo_custo, saida) {}

// TODO: comportamento por implementar
bool Silo::recebe(Item*) { return false; }
void Silo::atua(Maquina*, Terreno*) {}
bool Silo::melhora() { return false; }
std::string Silo::getDescricao() const { return ""; }
