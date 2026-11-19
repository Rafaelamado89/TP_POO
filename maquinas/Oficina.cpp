#include "Oficina.h"
#include "Item.h"
#include "Settings.h"

Oficina::Oficina(Direcao saida)
    : Maquina('O', Settings::oficina_custo, saida), placasFerro(0), silicioPuro(0), agua(0), kit(nullptr), instantesRestantes(0), melhorias(0) {}

Oficina::~Oficina() {
    delete kit;
}

//Por implementar
bool Oficina::recebe(Item*) { return false; }
void Oficina::atua(Maquina*, Terreno*) {}
bool Oficina::melhora() { return false; }
std::string Oficina::getDescricao() const { return ""; }
