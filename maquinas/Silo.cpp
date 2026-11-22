#include "Silo.h"
#include <sstream>
#include "Aleatorio.h"
#include "Item.h"
#include "Settings.h"

Silo::Silo(Direcao saida)
    : Maquina('S', Settings::silo_custo, saida),
      itens(nullptr), numItens(0), probPerda(Settings::silo_prob_perda) {}

Silo::~Silo() {
    for (int i = 0; i < numItens; i++) {
        delete itens[i];
    }
    delete[] itens;
}

// Aceita qualquer item, sem limite. O array cresce de uma posicao de cada vez, para nao
// ocupar mais memoria do que a necessaria. Fica dono do item.
bool Silo::recebe(Item* novo) {
    if (novo == nullptr) {
        return false;
    }
    Item** maior = new Item*[numItens + 1];
    for (int i = 0; i < numItens; i++) {
        maior[i] = itens[i];
    }
    maior[numItens] = novo;
    delete[] itens;
    itens = maior;
    if (numItens == 0) {
        marcaAtividade();   // o mais antigo e este, que acabou de chegar: so segue no instante seguinte
    }
    numItens++;
    return true;
}

Item* Silo::retiraMaisAntigo() {
    Item* antigo = itens[0];
    if (numItens == 1) {
        delete[] itens;
        itens = nullptr;
    } else {
        Item** menor = new Item*[numItens - 1];
        for (int i = 1; i < numItens; i++) {
            menor[i - 1] = itens[i];
        }
        delete[] itens;
        itens = menor;
    }
    numItens--;
    return antigo;
}

void Silo::atua(Maquina* destino, Terreno*) {
    if (numItens == 0 || agiuNesteInstante) {
        return;
    }
    if (Aleatorio::entre(1, 100) <= probPerda) {
        delete retiraMaisAntigo();
        return;
    }
    if (destino != nullptr && destino->recebe(itens[0])) {
        retiraMaisAntigo();   // o destino ficou com ele (e e agora o dono): nao se apaga
    }
}

bool Silo::melhora() { return false; }

std::string Silo::getDescricao() const {
    std::ostringstream texto;
    texto << "silo, itens: " << numItens << " (";
    for (int i = 0; i < numItens; i++) {
        texto << itens[i]->getSimbolo();
    }
    texto << "), perda: " << probPerda << "%";
    return texto.str();
}
