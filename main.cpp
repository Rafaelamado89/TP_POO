#include <exception>
#include <iostream>
#include <string>
#include "Fabrica.h"
#include "Posicao.h"
#include "Settings.h"
#include "Vista.h"

// Demonstracao do checkpoint 1. Os comandos (fabrica, carrega, lposicao, fim) so chegam no checkpoint 2:
// aqui chama-se diretamente a funcionalidade que eles vao usar.

namespace {
    // O painel ainda nao tem simulacao por tras: instante 0, os creditos iniciais, sem maquinas nem engenheiros
    void mostra(const Fabrica& fab) {
        Vista::mostra(fab, 0, Settings::fabrica_creditos_iniciais, 0, 0);
    }

    // O que o comando "lposicao <lc> [n]" vai fazer, so para o terreno (raio 0 = so a posicao indicada)
    void lposicao(const Fabrica& fab, const std::string& lc, int raio = 0) {
        std::cout << "> lposicao " << lc;
        if (raio != 0) {
            std::cout << ' ' << raio;
        }
        std::cout << '\n';

        Posicao p;
        if (!Posicao::deTexto(lc, p)) {
            std::cout << "Posicao invalida: '" << lc << "' (escreve-se com duas letras, ex.: ce)\n";
            return;
        }
        if (!fab.contem(p)) {
            std::cout << "A posicao " << lc << " fica fora da fabrica\n";
            return;
        }
        if (raio < 0) {
            std::cout << "O raio nao pode ser negativo\n";
            return;
        }
        std::cout << fab.descricaoArea(p, raio);
    }
}

int main() {
    // As fabricas sao criadas com new (como o farao os comandos) e libertadas no fim
    Fabrica* aleatoria = nullptr;
    Fabrica* doMapa = nullptr;

    try {
        // 1) O que o comando "fabrica <nl> <nc>" vai fazer: as dimensoes dadas, crateras e depositos ao acaso
        const int nl = 8, nc = 20;
        std::cout << "> fabrica " << nl << ' ' << nc << '\n';
        aleatoria = new Fabrica(nl, nc);
        aleatoria->distribuiAleatorio();
        mostra(*aleatoria);

        // 2) O que o comando "carrega <ficheiro>" vai fazer: se falhar, a fabrica nao e criada
        std::string erro;
        std::cout << "\n> carrega nao_existe.txt\n";
        Fabrica* falhada = Fabrica::carrega("nao_existe.txt", erro);   // devolve nullptr
        if (falhada == nullptr) {
            std::cout << "Nao foi possivel carregar: " << erro << '\n';
        }

        std::cout << "\n> carrega mapa1.txt\n";
        doMapa = Fabrica::carrega("mapa1.txt", erro);
        if (doMapa == nullptr) {
            std::cout << "Nao foi possivel carregar: " << erro << '\n';
        } else {
            mostra(*doMapa);

            // 3) lposicao, so para o terreno
            lposicao(*doMapa, "ac");      // deposito de ferro
            lposicao(*doMapa, "bh", 1);   // cratera e o quadrado de raio 1 a volta
            lposicao(*doMapa, "zz");      // fora da fabrica (6x10)
            lposicao(*doMapa, "c1");      // mal escrita
        }
    } catch (const std::exception& e) {
        // Os erros esperados sao tratados acima; isto e para que nenhuma excecao fique por tratar
        std::cerr << "Erro inesperado: " << e.what() << '\n';
    }

    // 4) O que o comando "fim" vai fazer: saida limpa, sem recursos por libertar
    std::cout << "\n> fim\n";
    delete aleatoria;
    delete doMapa;
    return 0;
}
