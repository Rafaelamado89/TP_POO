#ifndef SIMULADOR_H
#define SIMULADOR_H

#include <string>

class Comando;
class Fabrica;

// A interacao com o utilizador: le cada linha (do teclado, ou de um ficheiro atraves do comando executa),
// encontra o comando pelo nome e manda-o executar. E dona da fabrica e dos comandos, e e por ela que passa
// tudo o que se escreve na consola (as classes do modelo nao fazem I/O).
class Simulador {
public:
    Simulador();
    ~Simulador();

    // E dona de memoria dinamica (a fabrica e os comandos) e so ha um: nao se copia nem se atribui
    Simulador(const Simulador&) = delete;
    Simulador& operator=(const Simulador&) = delete;

    void corre();                              // o ciclo do teclado, ate ao comando fim
    bool processa(const std::string& linha);   // uma linha de comando, venha do teclado ou de um ficheiro

    // A fabrica (so existe depois do fabrica ou do carrega)
    bool temFabrica() const;
    Fabrica& getFabrica();
    const Fabrica& getFabrica() const;
    void instalaFabrica(Fabrica* nova);        // fica dona dela; so pode acontecer uma vez

    // Saida para o utilizador
    void mostraEcra() const;                   // a fabrica e o painel, atraves da Vista
    void informa(const std::string& texto) const;

    // O comando fim
    void termina();
    bool terminou() const;

    // Os comandos (para o ajuda)
    int getNumComandos() const;
    const Comando* getComando(int i) const;
    const Comando* procuraComando(const std::string& nome) const;   // nullptr se nao existir

private:
    void adiciona(Comando* comando);
    int indiceDe(const std::string& nome) const;                    // -1 se nao existir

    inline static const int maxComandos = 17;  // os comandos do enunciado

    Comando* comandos[maxComandos];            // colecao polimorfica: ponteiros para a base
    int numComandos;
    Fabrica* fabrica;                          // nullptr ate ao fabrica ou ao carrega
    bool terminado;
};

#endif //SIMULADOR_H
