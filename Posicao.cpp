#include "Posicao.h"

#include <stdexcept>
#include <string>

namespace {
    // Ha 26 letras, por isso cada coordenada vai de 0 ('a') a 25 ('z')
    const int maiorCoordenada = 'z' - 'a';
}

Posicao::Posicao() : linha(0), coluna(0) {
}

Posicao::Posicao(int linha, int coluna) : linha(linha), coluna(coluna) {
    if (linha < 0 || linha > maiorCoordenada || coluna < 0 || coluna > maiorCoordenada) {
        throw std::invalid_argument("Posicao: (" + std::to_string(linha) + ", " + std::to_string(coluna) +
                                    ") nao se escreve com duas letras");
    }
}

bool Posicao::deTexto(const std::string& texto, Posicao& resultado) {
    if (texto.size() != 2) {
        return false;
    }
    const char l = texto[0];
    const char c = texto[1];
    if (l < 'a' || l > 'z' || c < 'a' || c > 'z') {
        return false;
    }
    resultado = Posicao(l - 'a', c - 'a');
    return true;
}

int Posicao::getLinha() const {
    return linha;
}

int Posicao::getColuna() const {
    return coluna;
}

std::string Posicao::getTexto() const {
    return std::string(1, static_cast<char>('a' + linha)) + static_cast<char>('a' + coluna);
}
