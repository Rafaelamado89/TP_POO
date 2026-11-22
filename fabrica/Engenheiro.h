#ifndef ENGENHEIRO_H
#define ENGENHEIRO_H

#include <string>

class Maquina;

class Engenheiro {
public:
    explicit Engenheiro(const std::string& nome);

    int getId() const;
    const std::string& getNome() const;

    Maquina* getMaquina() const;
    void setMaquina(Maquina* maquina);

private:
    inline static int proximoId = 1;
    int id;
    std::string nome;
    Maquina* maquina;                          // nao e dono da maquina
};

#endif //ENGENHEIRO_H
