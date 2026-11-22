#include "Lancador.h"
#include "Item.h"
#include "Settings.h"

Lancador::Lancador(Direcao saida)
    : Maquina('L', Settings::lancador_custo, saida), item(nullptr), instantesRestantes(0), probPerda(Settings::lancador_prob_perda) {}

Lancador::~Lancador() {
    delete item;
}

bool Lancador::recebe(Item* novo) {
    if (novo == nullptr || item != nullptr) {
        return false;
    }
    item = novo;
    marcaAtividade();
    return true;
}

void Lancador::atua(Maquina*, Terreno*) {}

bool Lancador::melhora() { return false; }

std::string Lancador::getDescricao() const {
    if (item == nullptr) {
        return "lancador, item: nenhum";
    }
    return "lancador, item por lancar: " + item->getNome();
}
