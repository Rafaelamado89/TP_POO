#include "Oficina.h"
#include <sstream>
#include "Item.h"
#include "Settings.h"

Oficina::Oficina(Direcao saida)
    : Maquina('O', Settings::oficina_custo, saida), placasFerro(0), silicioPuro(0), agua(0), kit(nullptr), instantesRestantes(0), melhorias(0) {}

Oficina::~Oficina() {
    delete kit;
}

// O item recebido fica contado e e apagado (os ingredientes sao gastos na producao).
bool Oficina::recebe(Item* novo) {
    if (novo == nullptr) {
        return false;
    }
    char c = novo->getSimbolo();
    if (c == 'p' && placasFerro < Settings::oficina_receita_placas_ferro) {
        placasFerro++;
    } else if (c == 'i' && silicioPuro < Settings::oficina_receita_silicio_puro) {
        silicioPuro++;
    } else if (c == 'a' && agua < Settings::oficina_receita_agua) {
        agua++;
    } else {
        return false;
    }
    delete novo;
    return true;
}

void Oficina::atua(Maquina* destino, Terreno*) {
    if (kit == nullptr || agiuNesteInstante) {
        return;
    }
    if (destino != nullptr && destino->recebe(kit)) {
        kit = nullptr;
    }
}

bool Oficina::melhora() { return false; }

std::string Oficina::getDescricao() const {
    std::ostringstream texto;
    texto << "oficina, placas: " << placasFerro << ", silicio puro: " << silicioPuro << ", agua: " << agua;
    if (kit != nullptr) {
        texto << ", kit por entregar";
    }
    return texto.str();
}
