#ifndef COMANDO_H
#define COMANDO_H

#include <iosfwd>
#include <string>
#include "Direcao.h"

class Posicao;
class Simulador;

// Base dos comandos: cada um valida os seus parametros, executa e gera a sua propria ajuda.
// O Simulador guarda-os num array de ponteiros para esta base e chama o executa() sem saber qual e.
class Comando {
public:
    Comando(const std::string& nome, const std::string& sintaxe);
    virtual ~Comando();

    const std::string& getNome() const;
    const std::string& getSintaxe() const;
    virtual std::string getAjuda() const = 0;

    virtual bool precisaFabrica() const;

    // Valida os parametros (o resto da linha, depois do nome do comando) e executa.
    // Devolve false se o comando falhou; nesse caso o utilizador ja foi informado do motivo.
    virtual bool executa(Simulador& sim, std::istringstream& args) = 0;

protected:
    static bool semMaisParametros(std::istringstream& args);
    static bool paraInteiro(const std::string& texto, int& valor);
    static bool paraDirecao(const std::string& texto, Direcao& direcao);
    static bool posicaoNaFabrica(Simulador& sim, const std::string& texto, Posicao& posicao);

    bool erroSintaxe(Simulador& sim) const;

    std::string formataAjuda(const std::string& parametros, const std::string& efeito,
                             const std::string& falha, const std::string& exemplo) const;

private:
    std::string nome;
    std::string sintaxe;
};

#endif //COMANDO_H
