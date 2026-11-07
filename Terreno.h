#ifndef TERRENO_H
#define TERRENO_H

#include <string>


class Terreno {

public:
    enum class Tipo {
        Solo,
        Cratera,
        Ferro,
        Silicio,
        Gelo
    };

    Terreno();
    explicit Terreno(Tipo t, int qtd = 0);

    bool eDeposito() const;
    char getCaracter() const;
    static Tipo tipoDoMapa(char c);
    std::string getDescricao() const;

private:
    Tipo tipo;
    int quantidade;
};


#endif //TERRENO_H
