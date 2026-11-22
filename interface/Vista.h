#ifndef VISTA_H
#define VISTA_H

class Ecra;
class Fabrica;

// A apresentacao da simulacao: desenha a fabrica e o painel de estado num ecra virtual (Ecra) e so depois o passa
// para a consola. Nao guarda nada nem altera a fabrica: so le dela o que o desenho precisa.
class Vista {
public:
    Vista() = delete;

    static void mostra(const Fabrica& fab);

private:
    static int alturaFabrica(const Fabrica& fab);
    static int larguraFabrica(const Fabrica& fab);
    static void desenhaFabrica(Ecra& e, const Fabrica& fab);
    static void desenhaPainel(Ecra& e, const Fabrica& fab, int coluna, int altura);

    inline static const int grelhaLinha = 2;
    inline static const int grelhaColuna = 3;
    inline static const int espacoPainel = 2;
    inline static const int painelLargura = 35;
    inline static const int linhaResumo = 7;
    inline static const int painelAlturaMin = 9;
};

#endif //VISTA_H
