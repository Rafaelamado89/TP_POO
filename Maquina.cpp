#include "Maquina.h"

Maquina::Maquina(char simbolo, int custo, Direcao saida)
    : simbolo(simbolo), custo(custo), saida(saida) {}

Maquina::~Maquina() {}

char Maquina::getSimbolo() const { return simbolo; }
int Maquina::getCusto() const { return custo; }
Direcao Maquina::getSaida() const { return saida; }
void Maquina::setSaida(Direcao saida) { this->saida = saida; }


bool Maquina::melhora() { return false; }

//Por implementar
void Maquina::associa(Engenheiro*) {}
void Maquina::desassocia(Engenheiro*) {}
int Maquina::getNumEngenheiros() const { return 0; }
