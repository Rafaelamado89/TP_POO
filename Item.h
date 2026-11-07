//
// Created by Rafael on 07/11/2026.
//

#ifndef ITENS_H
#define ITENS_H
#include <string>


class Item {
  public:
    Item(const std::string& nome, char simbolo, int valor);

    char getSimbolo() const;
    int getValor() const;
    std::string& getNome() const;

  virtual Item* clona() const = 0;

  private:
    char simbolo;
    int valor;
    std::string nome;

};



#endif //ITENS_H
