#include "Lancador.h"
#include "Item.h"
#include "Settings.h"

Lancador::Lancador(Direcao saida)
    : Maquina('L', Settings::lancador_custo, saida), item(nullptr), instantesRestantes(0), probPerda(Settings::lancador_prob_perda) {}

Lancador::~Lancador() {
    delete item;
}

// Aceita qualquer item, mas so se nao tiver outro por lancar. Fica dono do item.
bool Lancador::recebe(Item* novo) {
    if (novo == nullptr || item != nullptr) {
        return false;
    }
    item = novo;
    marcaAtividade();
    return true;
}

// O lancamento (somar o valor aos creditos, a perda e a recarga de 4 instantes) e da entrega final
void Lancador::atua(Maquina*, Terreno*) {}

bool Lancador::melhora() { return false; }

std::string Lancador::getDescricao() const {
    if (item == nullptr) {
        return "item: nenhum";
    }
    return "item por lancar: " + item->getNome();
}
