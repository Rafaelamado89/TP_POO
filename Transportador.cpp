#include "Transportador.h"
#include "Settings.h"

Transportador::Transportador(Direcao saida) : Maquina('>', Settings::transportador_custo, saida) {}

// TODO: comportamento por implementar
bool Transportador::recebe(Item*) { return false; }
void Transportador::atua(Maquina*, Terreno*) {}
std::string Transportador::getDescricao() const { return ""; }
