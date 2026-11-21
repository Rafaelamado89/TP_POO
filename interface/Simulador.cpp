#include "Simulador.h"

#include <exception>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "Comando.h"
#include "ComandoAjuda.h"
#include "ComandoAtribui.h"
#include "ComandoAvanca.h"
#include "ComandoCarrega.h"
#include "ComandoCompra.h"
#include "ComandoContrata.h"
#include "ComandoDespede.h"
#include "ComandoEstado.h"
#include "ComandoExecuta.h"
#include "ComandoFabrica.h"
#include "ComandoFim.h"
#include "ComandoGrava.h"
#include "ComandoLposicao.h"
#include "ComandoMelhora.h"
#include "ComandoRecupera.h"
#include "ComandoRoda.h"
#include "ComandoVende.h"
#include "Fabrica.h"
#include "Vista.h"

// Os comandos sao criados uma vez, pela ordem do enunciado, e vivem ate ao fim do programa
Simulador::Simulador() : comandos{}, numComandos(0), fabrica(nullptr), terminado(false) {
    adiciona(new ComandoFabrica());
    adiciona(new ComandoCarrega());
    adiciona(new ComandoAvanca());
    adiciona(new ComandoCompra());
    adiciona(new ComandoVende());
    adiciona(new ComandoRoda());
    adiciona(new ComandoMelhora());
    adiciona(new ComandoContrata());
    adiciona(new ComandoAtribui());
    adiciona(new ComandoDespede());
    adiciona(new ComandoEstado());
    adiciona(new ComandoLposicao());
    adiciona(new ComandoGrava());
    adiciona(new ComandoRecupera());
    adiciona(new ComandoExecuta());
    adiciona(new ComandoAjuda());
    adiciona(new ComandoFim());
}

// A saida limpa: a fabrica (que apaga os seus terrenos e maquinas) e cada um dos comandos
Simulador::~Simulador() {
    delete fabrica;
    for (int i = 0; i < numComandos; ++i) {
        delete comandos[i];
    }
}

void Simulador::adiciona(Comando* comando) {
    if (numComandos == maxComandos) {
        delete comando;
        throw std::logic_error("Simulador: comandos a mais");
    }
    comandos[numComandos++] = comando;
}

void Simulador::corre() {
    informa("Simulador da fabrica em Marte. Comece com fabrica <nl> <nc> ou carrega <ficheiro>"
            " (ajuda mostra todos os comandos).");
    std::string linha;
    while (!terminado) {
        std::cout << "\n> ";
        if (!std::getline(std::cin, linha)) {
            terminado = true;   // acabou a entrada (ex.: Ctrl+Z): sai como com o fim
        } else {
            processa(linha);
        }
    }
}

// O mesmo caminho para o teclado e para o executa: so muda a origem da linha
bool Simulador::processa(const std::string& linha) {
    std::istringstream args(linha);
    std::string nome;
    if (!(args >> nome)) {
        return true;   // linha vazia: nao ha nada a fazer
    }

    const int i = indiceDe(nome);
    if (i < 0) {
        informa("Comando desconhecido: '" + nome + "' (ajuda mostra todos os comandos)");
        return false;
    }
    if (comandos[i]->precisaFabrica() && fabrica == nullptr) {
        informa("Ainda nao ha fabrica: o primeiro comando tem de ser fabrica ou carrega");
        return false;
    }

    // Os erros esperados ja foram tratados pelo comando; isto e para o inesperado, para nenhuma excecao
    // ficar por tratar
    try {
        return comandos[i]->executa(*this, args);
    } catch (const std::exception& e) {
        informa(std::string("Erro inesperado no comando ") + nome + ": " + e.what());
        return false;
    }
}

bool Simulador::temFabrica() const {
    return fabrica != nullptr;
}

Fabrica& Simulador::getFabrica() {
    if (fabrica == nullptr) {
        throw std::logic_error("Simulador: ainda nao ha fabrica");
    }
    return *fabrica;
}

const Fabrica& Simulador::getFabrica() const {
    if (fabrica == nullptr) {
        throw std::logic_error("Simulador: ainda nao ha fabrica");
    }
    return *fabrica;
}

void Simulador::instalaFabrica(Fabrica* nova) {
    if (fabrica != nullptr) {
        delete nova;   // fica dona dela mesmo quando a recusa
        throw std::logic_error("Simulador: a fabrica ja existe");
    }
    fabrica = nova;
}

void Simulador::mostraEcra() const {
    if (fabrica != nullptr) {
        Vista::mostra(*fabrica);
    }
}

void Simulador::informa(const std::string& texto) const {
    std::cout << texto << '\n';
}

void Simulador::termina() {
    terminado = true;
}

bool Simulador::terminou() const {
    return terminado;
}

int Simulador::getNumComandos() const {
    return numComandos;
}

const Comando* Simulador::getComando(int i) const {
    if (i < 0 || i >= numComandos) {
        throw std::out_of_range("Simulador: comando fora da lista");
    }
    return comandos[i];
}

const Comando* Simulador::procuraComando(const std::string& nome) const {
    const int i = indiceDe(nome);
    if (i < 0) {
        return nullptr;
    }
    return comandos[i];
}

int Simulador::indiceDe(const std::string& nome) const {
    for (int i = 0; i < numComandos; ++i) {
        if (comandos[i]->getNome() == nome) {
            return i;
        }
    }
    return -1;
}
