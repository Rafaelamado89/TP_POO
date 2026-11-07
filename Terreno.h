//
// Created by Luis Vieira on 07/11/2026.
//

#ifndef TERRENO_H
#define TERRENO_H

#include <string>

// Uma posicao da area da fabrica. Cada tipo de terreno (solo, cratera, deposito)
class Terreno {
public:
    virtual ~Terreno();

    virtual char getCaracter() const = 0;           // caracter no ecra
    virtual std::string getDescricao() const = 0;   // texto para o lposicao
    virtual Terreno* clona() const = 0;             // copia (usada ao copiar a fabrica)
};

#endif //TERRENO_H
