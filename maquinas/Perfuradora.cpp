#include "Perfuradora.h"
#include "Aleatorio.h"
#include "Item.h"
#include "MateriaPrima.h"
#include "Settings.h"
#include "Terreno.h"

Perfuradora::Perfuradora(Direcao saida)
    : Maquina('P', Settings::perfuradora_custo, saida), item(nullptr), instantes(0), probPerda(Settings::perfuradora_prob_perda) {}

Perfuradora::~Perfuradora() {
    delete item;
}

bool Perfuradora::recebe(Item*) { return false; }

// Se tiver um item por entregar, tenta entrega-lo. Se nao, a cada perfuradora_periodo instantes tira 1 unidade
// do terreno (so um deposito nao esgotado a tem), que se perde com a probabilidade perfuradora_prob_perda.
void Perfuradora::atua(Maquina* destino, Terreno* terreno) {
    if (agiuNesteInstante) {
        return;
    }
    if (item != nullptr) {
        if (destino != nullptr && destino->recebe(item)) {
            item = nullptr;
        }
        return;
    }
    if (++instantes < Settings::perfuradora_periodo) {
        return;
    }
    instantes = 0;
    Item* extraido = terreno->extrai();
    if (extraido == nullptr) {
        return;   // nao e um deposito (ou esgotou)
    }
    if (Aleatorio::entre(1, 100) <= probPerda) {
        delete extraido;
        return;
    }
    item = extraido;
    marcaAtividade();      // acabou de ser extraido: so sai no instante seguinte
}

bool Perfuradora::melhora() { return false; }

std::string Perfuradora::getDescricao() const {
    if (item == nullptr) {
        return "perfuradora, item: nenhum";
    }
    return "perfuradora, item: " + item->getNome();
}
