#include "Perfuradora.h"
#include "Item.h"
#include "Settings.h"

Perfuradora::Perfuradora(Direcao saida)
    : Maquina('P', Settings::perfuradora_custo, saida), item(nullptr), instantes(0), probPerda(Settings::perfuradora_prob_perda) {}

Perfuradora::~Perfuradora() {
    delete item;
}

// Por implementar
bool Perfuradora::recebe(Item*) { return false; }
void Perfuradora::atua(Maquina*, Terreno*) {}
bool Perfuradora::melhora() { return false; }
std::string Perfuradora::getDescricao() const { return ""; }
