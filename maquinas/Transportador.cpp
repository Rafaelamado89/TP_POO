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

bool Transportador::recebe(Item* novo) {
    if (novo == nullptr || item != nullptr) {
        return false;
    }
    item = novo;
    marcaAtividade();
    return true;
}

void Transportador::atua(Maquina* destino, Terreno*) {
    if (item == nullptr || agiuNesteInstante) {
        return;
    }
    if (destino != nullptr && destino->recebe(item)) {
        item = nullptr;
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
