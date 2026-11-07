#include "Silo.h"
#include "Item.h"
#include "Settings.h"

Silo::Silo(Direcao saida)
    : Maquina('S', Settings::silo_custo, saida), primeiro(nullptr), ultimo(nullptr), numItens(0),
      probPerda(Settings::silo_prob_perda) {}

Silo::~Silo() {
    while (primeiro != nullptr) {
        No* seguinte = primeiro->seguinte;
        delete primeiro->item;
        delete primeiro;
        primeiro = seguinte;
    }
}

// TODO: comportamento por implementar
bool Silo::recebe(Item*) { return false; }
void Silo::atua(Maquina*, Terreno*) {}
bool Silo::melhora() { return false; }
std::string Silo::getDescricao() const { return ""; }
