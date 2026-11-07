//
// Created by Rafael on 07/11/2026.
//

#ifndef PRODUTOSREFINADOS_H
#define PRODUTOSREFINADOS_H

#include "Item.h"

class ProdutosRefinados : public Item {
  public:
    ProdutosRefinados(const std::string& nome, char simbolo, int valor) :
        Item(nome, simbolo, valor) {}
};



#endif //PRODUTOSREFINADOS_H
