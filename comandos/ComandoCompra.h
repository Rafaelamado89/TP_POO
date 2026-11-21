#ifndef COMANDOCOMPRA_H
#define COMANDOCOMPRA_H

#include "Comando.h"

class Maquina;

// compra <tipo> <lc> <dir>: compra uma maquina e coloca-a na posicao lc, com a direcao de saida dir
class ComandoCompra : public Comando {
public:
    ComandoCompra();

    bool executa(Simulador& sim, std::istringstream& args) override;
    std::string getAjuda() const override;

private:
    static bool tipoValido(const std::string& texto);
    // O unico sitio que traduz a letra do tipo (p t r o s l) na classe da maquina
    static Maquina* criaMaquina(char tipo, Direcao saida);
};

#endif //COMANDOCOMPRA_H
