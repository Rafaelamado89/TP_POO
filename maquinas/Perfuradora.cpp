#include "Perfuradora.h"
#include "Item.h"
#include "Settings.h"

Perfuradora::Perfuradora(Direcao saida)
    : Maquina('P', Settings::perfuradora_custo, saida), item(nullptr), instantes(0), probPerda(Settings::perfuradora_prob_perda) {}

Perfuradora::~Perfuradora() {
    delete item;
}

// Nao aceita itens de outras maquinas
bool Perfuradora::recebe(Item*) { return false; }

// Por agora so entrega o item que tiver (a extracao do deposito e a perda sao da entrega final)
void Perfuradora::atua(Maquina* destino, Terreno*) {
    if (item == nullptr || agiuNesteInstante) {
        return;
    }
    if (destino != nullptr && destino->recebe(item)) {
        item = nullptr;
    }
}

bool Perfuradora::melhora() { return false; }

std::string Perfuradora::getDescricao() const {
    if (item == nullptr) {
        return "item: nenhum";
    }
    return "item: " + item->getNome();
}
