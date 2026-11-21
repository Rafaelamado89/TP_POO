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

    virtual char getSimbolo() const;   // o transportador muda de simbolo consoante leva ou nao um item
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

    // Chamada pela fabrica no fim de cada instante, depois de todas as maquinas terem atuado
    void fimInstante();

protected:
    // "Acabei de receber (ou produzir) um item neste instante": o item so avanca no instante seguinte.
    // E isto que garante que um item anda no maximo uma posicao por instante, seja qual for a ordem
    // pela qual a fabrica chama as maquinas.
    bool agiuNesteInstante;
    void marcaAtividade();

private:
    char simbolo;
    int custo;
    Direcao saida;
    std::vector<Engenheiro*> engenheiros;
};

#endif //MAQUINA_H
