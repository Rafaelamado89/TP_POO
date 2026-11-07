#ifndef POSICAO_H
#define POSICAO_H

#include <string>

// Uma posicao da fabrica: linha e coluna a partir de 0. No texto escreve-se com duas letras,
// primeiro a linha e depois a coluna ("aa" e o canto superior esquerdo, "ce" e (2, 4)).
class Posicao {
public:
    Posicao();
    Posicao(int linha, int coluna);

    static bool deTexto(const std::string& texto, Posicao& resultado);

    int getLinha() const;
    int getColuna() const;
    std::string getTexto() const;

private:
    int linha;
    int coluna;
};


#endif //POSICAO_H
