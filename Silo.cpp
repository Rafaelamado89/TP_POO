#include "Silo.h"
#include "Item.h"
#include "Settings.h"

Silo::Silo(Direcao saida)
    : Maquina('S', Settings::silo_custo, saida),
      itens(nullptr), numItens(0), probPerda(Settings::silo_prob_perda) {}

Silo::~Silo() {}

// por Implementar
bool Silo::recebe(Item*) { return false; }
void Silo::atua(Maquina*, Terreno*) {}
bool Silo::melhora() { return false; }
std::string Silo::getDescricao() const { return ""; }
