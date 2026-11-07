#include "Lancador.h"
#include "Item.h"
#include "Settings.h"

Lancador::Lancador(Direcao saida)
    : Maquina('L', Settings::lancador_custo, saida), item(nullptr), instantesRestantes(0), probPerda(Settings::lancador_prob_perda) {}

Lancador::~Lancador() {
    delete item;
}

// Por implementar
bool Lancador::recebe(Item*) { return false; }
void Lancador::atua(Maquina*, Terreno*) {}
bool Lancador::melhora() { return false; }
std::string Lancador::getDescricao() const { return ""; }
