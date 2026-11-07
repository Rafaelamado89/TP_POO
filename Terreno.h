#ifndef TERRENO_H
#define TERRENO_H


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
    Terreno(Tipo t, int qtd = 0);

    bool eDeposito() const;
    char getCaracter() const;
private:
    Tipo tipo;
    int quantidade;
};


#endif //TERRENO_H
