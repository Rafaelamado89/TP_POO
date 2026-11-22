#include "Comando.h"

#include <sstream>
#include <string>
#include "Fabrica.h"
#include "Posicao.h"
#include "Simulador.h"

Comando::Comando(const std::string& nome, const std::string& sintaxe) : nome(nome), sintaxe(sintaxe) {
}

Comando::~Comando() {
}

const std::string& Comando::getNome() const {
    return nome;
}

const std::string& Comando::getSintaxe() const {
    return sintaxe;
}

bool Comando::precisaFabrica() const {
    return true;
}

bool Comando::semMaisParametros(std::istringstream& args) {
    std::string sobra;
    return !(args >> sobra);
}

// So aceita se o texto todo for um inteiro: "12" sim; "abc", "3x" e "1.5" nao
bool Comando::paraInteiro(const std::string& texto, int& valor) {
    std::istringstream is(texto);
    int lido = 0;
    char sobra = 0;
    if (!(is >> lido) || (is >> sobra)) {
        return false;
    }
    valor = lido;
    return true;
}

bool Comando::paraDirecao(const std::string& texto, Direcao& direcao) {
    if (texto == "c") {
        direcao = Cima;
    } else if (texto == "b") {
        direcao = Baixo;
    } else if (texto == "e") {
        direcao = Esquerda;
    } else if (texto == "d") {
        direcao = Direita;
    } else {
        return false;
    }
    return true;
}

bool Comando::posicaoNaFabrica(Simulador& sim, const std::string& texto, Posicao& posicao) {
    if (!Posicao::deTexto(texto, posicao)) {
        sim.informa("Posicao invalida: '" + texto + "' (duas letras, linha e coluna, ex.: ce)");
        return false;
    }
    const Fabrica& fab = sim.getFabrica();
    if (!fab.contem(posicao)) {
        sim.informa("A posicao " + texto + " fica fora da fabrica (" + std::to_string(fab.getLinhas()) + "x" +
                    std::to_string(fab.getColunas()) + ")");
        return false;
    }
    return true;
}

bool Comando::erroSintaxe(Simulador& sim) const {
    sim.informa("Sintaxe: " + sintaxe + "   (ajuda " + nome + " para mais detalhes)");
    return false;
}

std::string Comando::formataAjuda(const std::string& parametros, const std::string& efeito,
                                  const std::string& falha, const std::string& exemplo) const {
    std::ostringstream texto;
    texto << "Sintaxe: " << sintaxe << '\n'
          << "Parametros: " << parametros << '\n'
          << "Efeito: " << efeito << '\n'
          << "Falha se: " << falha << '\n'
          << "Exemplo: " << exemplo;
    return texto.str();
}
