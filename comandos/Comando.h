#ifndef COMANDO_H
#define COMANDO_H

#include <iosfwd>     // so declara o std::istringstream: aqui so e recebido por referencia
#include <string>
#include "Direcao.h"

class Posicao;
class Simulador;

// Base da hierarquia dos comandos do utilizador. Cada comando e uma classe filha (fabrica, carrega, compra,
// vende, roda, melhora, avanca, contrata, atribui, despede, estado, lposicao, grava, recupera, executa,
// ajuda, fim) que valida os seus parametros, se executa e gera a sua propria ajuda.
// O Simulador guarda-os todos num array de ponteiros para esta base e chama o executa() sem saber qual e.
class Comando {
public:
    Comando(const std::string& nome, const std::string& sintaxe);
    virtual ~Comando();

    const std::string& getNome() const;
    const std::string& getSintaxe() const;      // sintaxe resumida (ajuda sem parametro)
    virtual std::string getAjuda() const = 0;   // sintaxe, parametros, efeito, quando falha, exemplo

    // Quase todos os comandos precisam de uma fabrica ja criada; os que nao precisam redefinem esta funcao.
    virtual bool precisaFabrica() const;

    // Valida os parametros (o resto da linha, depois do nome do comando) e executa.
    // Devolve false se o comando falhou; nesse caso o utilizador ja foi informado do motivo.
    virtual bool executa(Simulador& sim, std::istringstream& args) = 0;

protected:
    // Validacoes que se repetem em varios comandos
    static bool semMaisParametros(std::istringstream& args);
    static bool paraInteiro(const std::string& texto, int& valor);
    static bool paraDirecao(const std::string& texto, Direcao& direcao);
    static bool posicaoNaFabrica(Simulador& sim, const std::string& texto, Posicao& posicao);

    // Informa a sintaxe certa e devolve false (para usar como "return erroSintaxe(sim);")
    bool erroSintaxe(Simulador& sim) const;

    // A ajuda detalhada, sempre com o mesmo formato
    std::string formataAjuda(const std::string& parametros, const std::string& efeito,
                             const std::string& falha, const std::string& exemplo) const;

private:
    std::string nome;
    std::string sintaxe;
};

#endif //COMANDO_H
