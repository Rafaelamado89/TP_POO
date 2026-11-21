#include "Refinaria.h"
#include "Item.h"
#include "Settings.h"

Refinaria::Refinaria(Direcao saida)
    : Maquina('R', Settings::refinaria_custo, saida), item(nullptr), instantesRestantes(0) {}

Refinaria::~Refinaria() {
    delete item;
}

// Aceita apenas materias-primas (f, s, g), uma de cada vez e so se estiver vazia. Fica dona do item.
bool Refinaria::recebe(Item* novo) {
    if (novo == nullptr || item != nullptr) {
        return false;
    }
    char c = novo->getSimbolo();
    if (c != 'f' && c != 's' && c != 'g') {
        return false;
    }
    item = novo;
    marcaAtividade();
    return true;
}

// Por agora so entrega o item que tiver (a transformacao, que demora 4 instantes, e da entrega final)
void Refinaria::atua(Maquina* destino, Terreno*) {
    if (item == nullptr || agiuNesteInstante) {
        return;
    }
    if (destino != nullptr && destino->recebe(item)) {
        item = nullptr;
    }
}

std::string Refinaria::getDescricao() const {
    if (item == nullptr) {
        return "item: nenhum";
    }
    return "item: " + item->getNome();
}
