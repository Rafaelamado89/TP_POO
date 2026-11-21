#include "Maquina.h"

Maquina::Maquina(char simbolo, int custo, Direcao saida)
    : agiuNesteInstante(false), simbolo(simbolo), custo(custo), saida(saida) {}

Maquina::~Maquina() {}

char Maquina::getSimbolo() const { return simbolo; }
int Maquina::getCusto() const { return custo; }
Direcao Maquina::getSaida() const { return saida; }
void Maquina::setSaida(Direcao saida) { this->saida = saida; }

void Maquina::marcaAtividade() { agiuNesteInstante = true; }
void Maquina::fimInstante() { agiuNesteInstante = false; }


bool Maquina::melhora() { return false; }

//Por implementar
void Maquina::associa(Engenheiro*) {}
void Maquina::desassocia(Engenheiro*) {}
int Maquina::getNumEngenheiros() const { return 0; }
