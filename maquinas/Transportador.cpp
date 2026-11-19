#include "Transportador.h"
#include "Item.h"
#include "Settings.h"

Transportador::Transportador(Direcao saida)
    : Maquina('>', Settings::transportador_custo, saida), item(nullptr) {}

Transportador::~Transportador() {
    delete item;
}

//Por implementar
bool Transportador::recebe(Item*) { return false; }
void Transportador::atua(Maquina*, Terreno*) {}
std::string Transportador::getDescricao() const { return ""; }
