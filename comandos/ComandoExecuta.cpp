#include "ComandoExecuta.h"

#include <fstream>
#include <sstream>
#include <string>
#include "Simulador.h"

ComandoExecuta::ComandoExecuta() : Comando("executa", "executa <nome-do-ficheiro>"), numEmCurso(0) {
}

// Pode ser usado antes de haver fabrica (o proprio ficheiro pode cria-la)
bool ComandoExecuta::precisaFabrica() const {
    return false;
}

bool ComandoExecuta::executa(Simulador& sim, std::istringstream& args) {
    std::string nomeFicheiro;
    if (!(args >> nomeFicheiro) || !semMaisParametros(args)) {
        return erroSintaxe(sim);
    }
    if (estaEmCurso(nomeFicheiro)) {
        sim.informa("O ficheiro '" + nomeFicheiro + "' ja esta a ser executado: ignorado, para nao entrar em ciclo");
        return false;
    }
    if (numEmCurso == maxEmCurso) {
        sim.informa("Demasiados ficheiros executados uns dentro dos outros (maximo " +
                    std::to_string(maxEmCurso) + ")");
        return false;
    }
    std::ifstream ficheiro(nomeFicheiro);
    if (!ficheiro) {
        sim.informa("Nao foi possivel abrir o ficheiro '" + nomeFicheiro + "'");
        return false;
    }

    // Cada linha vai para o mesmo processa do teclado: so muda a origem do texto.
    // O processa apanha as excecoes, por isso o numEmCurso volta sempre a descer.
    emCurso[numEmCurso++] = nomeFicheiro;
    int total = 0, falhados = 0;
    std::string linha;
    while (!sim.terminou() && std::getline(ficheiro, linha)) {
        if (!linha.empty() && linha.back() == '\r') {
            linha.pop_back();   // ficheiros escritos no Windows
        }
        std::istringstream temTexto(linha);
        std::string palavra;
        if (!(temTexto >> palavra)) {
            continue;   // linha vazia
        }
        sim.informa("\n> " + linha);   // mostra o comando, como se tivesse sido escrito
        ++total;
        if (!sim.processa(linha)) {
            ++falhados;
        }
    }
    --numEmCurso;

    sim.informa("[" + nomeFicheiro + ": " + std::to_string(total) + " comandos, " + std::to_string(falhados) +
                " falharam]");
    return falhados == 0;
}

bool ComandoExecuta::estaEmCurso(const std::string& nomeFicheiro) const {
    for (int i = 0; i < numEmCurso; ++i) {
        if (emCurso[i] == nomeFicheiro) {
            return true;
        }
    }
    return false;
}

std::string ComandoExecuta::getAjuda() const {
    return formataAjuda(
        "<nome-do-ficheiro> um ficheiro de texto com um comando por linha, escrito como no teclado",
        "executa os comandos do ficheiro, pela ordem, exatamente como se fossem escritos no teclado (as linhas "
        "vazias sao ignoradas); no fim, diz quantos comandos falharam",
        "falta o nome ou ha parametros a mais; o ficheiro nao existe; o ficheiro ja esta a ser executado "
        "(por exemplo, um ficheiro que se executa a si proprio)",
        "executa teste1.txt");
}
