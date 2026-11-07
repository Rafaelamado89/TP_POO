//
// Created by Luis Vieira on 07/11/2026.
//

#ifndef ALEATORIO_H
#define ALEATORIO_H

#include <random>

class Aleatorio {
public:
    Aleatorio() = delete;
    static int entre(int min, int max);
    static std::mt19937& gerador();
};


#endif //ALEATORIO_H
