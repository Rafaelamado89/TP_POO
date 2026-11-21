#ifndef VISTA_H
#define VISTA_H

class Ecra;
class Fabrica;

// A apresentacao da simulacao: desenha a fabrica e o painel de estado num ecra virtual (Ecra) e so depois o passa
// para a consola. Nao guarda nada nem altera a fabrica: so le dela o que o desenho precisa.
class Vista {
public:
    Vista() = delete;   // so tem funcoes static (caixa de ferramentas, como a Aleatorio)

    // A fabrica (moldura, regua e um caracter por posicao: a maquina, se houver, ou o terreno) e, ao lado,
    // o painel de estado (instante, creditos, maquinas, engenheiros e o resumo do ultimo instante).
    static void mostra(const Fabrica& fab);

private:
    static int alturaFabrica(const Fabrica& fab);
    static int larguraFabrica(const Fabrica& fab);
    static void desenhaFabrica(Ecra& e, const Fabrica& fab);
    static void desenhaPainel(Ecra& e, const Fabrica& fab, int coluna, int altura);

    // Disposicao igual a do exemplo do enunciado (p. 2)
    inline static const int grelhaLinha = 2;       // linha do ecra onde fica a linha 0 da fabrica
    inline static const int grelhaColuna = 3;      // coluna do ecra onde fica a coluna 0 da fabrica
    inline static const int espacoPainel = 2;      // colunas vazias entre a fabrica e o painel
    inline static const int painelLargura = 35;
    inline static const int linhaResumo = 7;       // primeira linha do resumo do ultimo instante
    inline static const int painelAlturaMin = 9;   // moldura + 4 valores + linha vazia + titulo + 1 do resumo
};


#endif //VISTA_H
