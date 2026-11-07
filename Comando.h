#ifndef COMANDO_H
#define COMANDO_H

#include <string>
#include <vector>

class Fabrica;

// Base da hierarquia dos comandos do utilizador. Cada comando e uma classe filha (fabrica, carrega, compra,
// vende, roda, melhora, avanca, contrata, atribui, despede, estado, lposicao, grava, recupera, executa,
// ajuda, fim) que valida os seus parametros, se executa e gera a sua propria ajuda.
class Comando {
public:
    virtual ~Comando();

    // Valida os parametros (args) e executa o comando. A fabrica e passada por referencia ao ponteiro porque
    // os comandos fabrica e carrega e que a criam.
    virtual void executa(Fabrica*& fabrica, const std::vector<std::string>& args) = 0;

    // Sintaxe, parametros, efeito, condicoes em que falha e um exemplo (comando ajuda).
    virtual std::string getAjuda() const = 0;
};

#endif //COMANDO_H
