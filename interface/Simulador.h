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

    void corre();
    bool processa(const std::string& linha);

    bool temFabrica() const;
    Fabrica& getFabrica();
    const Fabrica& getFabrica() const;
    void instalaFabrica(Fabrica* nova);

    void mostraEcra() const;
    void informa(const std::string& texto) const;

    void termina();
    bool terminou() const;

    int getNumComandos() const;
    const Comando* getComando(int i) const;
    const Comando* procuraComando(const std::string& nome) const;

private:
    void adiciona(Comando* comando);
    int indiceDe(const std::string& nome) const;

    inline static const int maxComandos = 17;

    Comando* comandos[maxComandos];
    int numComandos;
    Fabrica* fabrica;
    bool terminado;
};

#endif //SIMULADOR_H
