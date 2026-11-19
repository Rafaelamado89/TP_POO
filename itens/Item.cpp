//
// Created by Rafael on 07/11/2026.
//

#include "Item.h"

Item::Item(const std::string& nome, char simbolo, int valor)
    : simbolo(simbolo), valor(valor), nome(nome) {}

Item::~Item() {}

char Item::getSimbolo() const { return simbolo; }
int Item::getValor() const { return valor; }
const std::string& Item::getNome() const { return nome; }
