//
// Created by Luis Vieira on 07/11/2026.
//

#ifndef TERRENO_H
#define TERRENO_H

#include <string>

class MateriaPrima;


class Terreno {
public:
    virtual ~Terreno();

    virtual char getCaracter() const = 0;
    virtual std::string getDescricao() const = 0;
    virtual Terreno* clona() const = 0;

    virtual MateriaPrima* extrai();
};

#endif //TERRENO_H
