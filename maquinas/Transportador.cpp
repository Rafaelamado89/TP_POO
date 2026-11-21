#include "Transportador.h"
#include <sstream>
#include "Item.h"
#include "Settings.h"

Transportador::Transportador(Direcao saida)
    : Maquina('>', Settings::transportador_custo, saida), item(nullptr) {}

Transportador::~Transportador() {
    delete item;
}

char Transportador::getSimbolo() const {
    if (item != nullptr) {
        return item->getSimbolo();
    }
    switch (getSaida()) {
        case Cima:
            return '^';
        case Baixo:
            return 'v';
        case Esquerda:
            return '<';
        default:
            return '>';
    }
}

// So aceita se estiver vazio. Fica dono do item.
bool Transportador::recebe(Item* novo) {
    if (novo == nullptr || item != nullptr) {
        return false;
    }
    item = novo;
    marcaAtividade();   // acabou de chegar: so segue no instante seguinte
    return true;
}

void Transportador::atua(Maquina* destino, Terreno*) {
    if (item == nullptr || agiuNesteInstante) {
        return;
    }
    if (destino != nullptr && destino->recebe(item)) {
        item = nullptr;   // o destino ficou com ele (e e agora o dono)
    }
}

std::string Transportador::getDescricao() const {
    std::ostringstream texto;
    texto << "transportador, item: ";
    if (item == nullptr) {
        texto << "nenhum";
    } else {
        texto << item->getNome();
    }
    return texto.str();
}
