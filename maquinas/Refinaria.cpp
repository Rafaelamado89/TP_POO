#include "Refinaria.h"
#include "Item.h"
#include "Settings.h"

Refinaria::Refinaria(Direcao saida)
    : Maquina('R', Settings::refinaria_custo, saida), item(nullptr), instantesRestantes(0) {}

Refinaria::~Refinaria() {
    delete item;
}

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

// Por agora fica com a materia-prima que recebeu: nao a pode entregar sem a refinar
void Refinaria::atua(Maquina*, Terreno*) {}

std::string Refinaria::getDescricao() const {
    if (item == nullptr) {
        return "refinaria, item: nenhum";
    }
    return "refinaria, item: " + item->getNome();
}
