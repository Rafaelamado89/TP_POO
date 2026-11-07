#include "Oficina.h"
#include "Settings.h"

Oficina::Oficina(Direcao saida) : Maquina('O', Settings::oficina_custo, saida) {}

// TODO: comportamento por implementar
bool Oficina::recebe(Item*) { return false; }
void Oficina::atua(Maquina*, Terreno*) {}
bool Oficina::melhora() { return false; }
std::string Oficina::getDescricao() const { return ""; }
