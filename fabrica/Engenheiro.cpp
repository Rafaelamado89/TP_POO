#include "Engenheiro.h"

Engenheiro::Engenheiro(const std::string& nome) : id(proximoId++), nome(nome), maquina(nullptr) {}

int Engenheiro::getId() const { return id; }
const std::string& Engenheiro::getNome() const { return nome; }
Maquina* Engenheiro::getMaquina() const { return maquina; }
void Engenheiro::setMaquina(Maquina* maquina) { this->maquina = maquina; }
