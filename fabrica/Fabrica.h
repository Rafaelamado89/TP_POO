//
// Created by Luis Vieira on 07/11/2026.
//

#ifndef FABRICA_H
#define FABRICA_H

#include <iosfwd>
#include <string>
#include <vector>

class Maquina;
class Posicao;
class Terreno;

// A area da fabrica e o estado da simulacao: o terreno e a maquina de cada posicao, os creditos, o instante,
// o total enviado para a Terra e o resumo do ultimo instante. E a dona dos terrenos e das maquinas.
// Nao faz I/O com o utilizador: o que ha para mostrar devolve-o em texto.
class Fabrica {
public:
    explicit Fabrica(int nl, int nc);
    ~Fabrica();

    // Nao se copia: e dona de memoria dinamica e a copia gerada so copiaria os ponteiros
    Fabrica(const Fabrica&) = delete;
    Fabrica& operator=(const Fabrica&) = delete;

    static int maxLinhas();
    static int maxColunas();
    static bool dimensoesValidas(int nl, int nc);
    static Fabrica* carrega(const std::string& nomeFicheiro, std::string& erro);   // nullptr se falhar
    void distribuiAleatorio();

    int getLinhas() const;
    int getColunas() const;
    char getCaracter(int l, int c) const;
    bool contem(const Posicao& p) const;

    std::string descricaoPosicao(const Posicao& p) const;
    std::string descricaoArea(const Posicao& centro, int raio) const;
    std::string descricaoEstado() const;

    int getInstante() const;
    int getCreditos() const;
    int getNumMaquinas() const;
    int getNumEngenheiros() const;
    const std::string& getResumoUltimoInstante() const;

    // Fica sempre com a maquina: se a compra falhar, apaga-a (e diz porque em "erro")
    bool compra(Maquina* nova, const Posicao& p, std::string& erro);
    Maquina* getMaquina(const Posicao& p);               // nullptr se nao houver maquina
    const Maquina* getMaquina(const Posicao& p) const;
    bool removeMaquina(const Posicao& p);
    void recebeCreditos(int quantia);

    void avancaInstante();

private:
    int indice(int l, int c) const;
    int indice(const Posicao& p) const;
    Maquina* destinoDe(int l, int c) const;
    std::string descricaoMaquina(int i) const;

    bool leMapa(std::istream& ficheiro, std::string& erro);
    static Terreno* criaTerreno(char caracter);
    void coloca(char caracter, int quantos, int& livres);

    inline static const int numTiposItem = 7;

    int nLinhas;
    int nColunas;
    std::vector<Terreno*> grelha;      // um terreno por posicao, indice l * nColunas + c (a fabrica e a dona)
    std::vector<Maquina*> maquinas;
    int creditos;
    int instante;
    int enviados[numTiposItem];
    std::string resumoUltimoInstante;
};

#endif //FABRICA_H
