#include "Perfuradora.h"
#include "Settings.h"

Perfuradora::Perfuradora(Direcao saida) : Maquina('P', Settings::perfuradora_custo, saida) {}

// TODO: comportamento por implementar
bool Perfuradora::recebe(Item*) { return false; }
void Perfuradora::atua(Maquina*, Terreno*) {}
bool Perfuradora::melhora() { return false; }
std::string Perfuradora::getDescricao() const { return ""; }
