#ifndef MAQUINA_H
#define MAQUINA_H

#include <string>
#include <vector>
#include "Direcao.h"

#include "Item.h"
#include "Terreno.h"
#include "Engenheiro.h"

class Maquina {
public:
    Maquina(char simbolo, int custo, Direcao saida);
    virtual ~Maquina();

    char getSimbolo() const;
    int getCusto() const;
    Direcao getSaida() const;
    void setSaida(Direcao saida);	// comando roda

    virtual bool recebe(Item* item) = 0;
    virtual void atua(Maquina* destino, Terreno* terreno) = 0;
    virtual bool melhora(); 	// comando melhora
    virtual std::string getDescricao() const = 0;

    void associa(Engenheiro* e);
    void desassocia(Engenheiro* e);
    int getNumEngenheiros() const;

private:
    char simbolo;
    int custo;
    Direcao saida;
    std::vector<Engenheiro*> engenheiros;
};

#endif //MAQUINA_H
