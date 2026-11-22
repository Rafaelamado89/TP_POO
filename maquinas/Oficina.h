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
    int placasFerro;
    int silicioPuro;
    int agua;
    Item* kit;
    int instantesRestantes;
    int melhorias;
};

#endif //OFICINA_H
