#ifndef ENGENHEIRO_H
#define ENGENHEIRO_H

#include <string>

class Maquina;

// Engenheiro contratado pelo gestor. Tem um nome e um id atribuido automaticamente (o primeiro e o 1).
// Esta livre ou associado a uma maquina, a qual acelera.
class Engenheiro {
public:
    explicit Engenheiro(const std::string& nome);

    int getId() const;
    const std::string& getNome() const;

    Maquina* getMaquina() const;               // nullptr se estiver livre
    void setMaquina(Maquina* maquina);         // comando atribui

private:
    inline static int proximoId = 1;
    int id;
    std::string nome;
    Maquina* maquina;                          // nao e dono da maquina
};

#endif //ENGENHEIRO_H
