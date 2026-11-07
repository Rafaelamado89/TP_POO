#include "Lancador.h"
#include "Settings.h"

Lancador::Lancador(Direcao saida) : Maquina('L', Settings::lancador_custo, saida) {}

// TODO: comportamento por implementar
bool Lancador::recebe(Item*) { return false; }
void Lancador::atua(Maquina*, Terreno*) {}
bool Lancador::melhora() { return false; }
std::string Lancador::getDescricao() const { return ""; }
