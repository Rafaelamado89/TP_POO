#include "Refinaria.h"
#include "Item.h"
#include "Settings.h"

Refinaria::Refinaria(Direcao saida)
    : Maquina('R', Settings::refinaria_custo, saida), item(nullptr), instantesRestantes(0) {}

Refinaria::~Refinaria() {
    delete item;
}

// Por implementar
bool Refinaria::recebe(Item*) { return false; }
void Refinaria::atua(Maquina*, Terreno*) {}
std::string Refinaria::getDescricao() const { return ""; }
