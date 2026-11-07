#ifndef OFICINA_H
#define OFICINA_H

#include "Maquina.h"


class Oficina : public Maquina {
public:
    explicit Oficina(Direcao saida);
    ~Oficina();

    bool recebe(Item* item) override;
    void atua(Maquina* destino, Terreno* terreno) override;
    bool melhora() override;
    std::string getDescricao() const override;

private:
    int placasFerro;          // placas de ferro ja recebidas para a receita
    int silicioPuro;          // silicio puro ja recebido para a receita
    int agua;                 // agua ja recebida para a receita
    Item* kit;                // kit produzido por entregar; nullptr se nao tiver
    int instantesRestantes;   // instantes que faltam para acabar a producao (0 = nenhuma em curso)
    int melhorias;            // num de melhorias ja feitas
};

#endif //OFICINA_H
