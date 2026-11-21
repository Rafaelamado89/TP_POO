//
// Created by Luis Vieira on 07/11/2026.
//

#ifndef FABRICA_H
#define FABRICA_H

#include <iosfwd>     // so declara o std::istream: aqui so e recebido por referencia
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

    // Por agora nao se copia nem se atribui: e dona de memoria dinamica (terrenos e maquinas) e a copia
    // gerada pelo compilador so copiaria os ponteiros. A copia profunda chega com o comando grava.
    Fabrica(const Fabrica&) = delete;
    Fabrica& operator=(const Fabrica&) = delete;

    // Criacao (comandos fabrica e carrega)
    static int maxLinhas();
    static int maxColunas();
    static bool dimensoesValidas(int nl, int nc);
    static Fabrica* carrega(const std::string& nomeFicheiro, std::string& erro);   // nullptr se falhar
    void distribuiAleatorio();

    // O mapa (Vista)
    int getLinhas() const;
    int getColunas() const;
    char getCaracter(int l, int c) const;   // a maquina, se houver; senao, o terreno
    bool contem(const Posicao& p) const;

    // Descricoes em texto (comandos lposicao e estado)
    std::string descricaoPosicao(const Posicao& p) const;
    std::string descricaoArea(const Posicao& centro, int raio) const;
    std::string descricaoEstado() const;

    // O estado da simulacao (painel)
    int getInstante() const;
    int getCreditos() const;
    int getNumMaquinas() const;
    int getNumEngenheiros() const;
    const std::string& getResumoUltimoInstante() const;   // uma linha por acontecimento

    // As maquinas
    // Fica sempre com a maquina: se a compra falhar, apaga-a (e diz porque em "erro")
    bool compra(Maquina* nova, const Posicao& p, std::string& erro);
    Maquina* getMaquina(const Posicao& p);               // nullptr se nao houver maquina
    const Maquina* getMaquina(const Posicao& p) const;
    bool removeMaquina(const Posicao& p);                // apaga-a (e os itens que tiver); false se nao havia
    void recebeCreditos(int quantia);

    // O tempo (comando avanca)
    void avancaInstante();

private:
    int indice(int l, int c) const;
    int indice(const Posicao& p) const;
    Maquina* destinoDe(int l, int c) const;   // a vizinha na direcao de saida da maquina em (l, c)
    std::string descricaoMaquina(int i) const;

    bool leMapa(std::istream& ficheiro, std::string& erro);
    // Cria o terreno que corresponde ao caracter do mapa ('.', '#', '%', '$', '~'); nullptr se for invalido
    static Terreno* criaTerreno(char caracter);
    void coloca(char caracter, int quantos, int& livres);

    inline static const int numTiposItem = 7;   // os itens do enunciado (p. 3)

    int nLinhas;
    int nColunas;
    std::vector<Terreno*> grelha;      // um terreno por posicao, indice l * nColunas + c (a fabrica e a dona)
    std::vector<Maquina*> maquinas;    // a maquina de cada posicao, com o mesmo indice; nullptr = sem maquina
    int creditos;
    int instante;
    int enviados[numTiposItem];        // total enviado para a Terra de cada tipo de item, desde o inicio
    std::string resumoUltimoInstante;
};


#endif //FABRICA_H
