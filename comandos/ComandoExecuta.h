#ifndef COMANDOEXECUTA_H
#define COMANDOEXECUTA_H

#include <string>
#include "Comando.h"

// executa <nome-do-ficheiro>: executa os comandos de um ficheiro, um por linha, como se viessem do teclado
class ComandoExecuta : public Comando {
public:
    ComandoExecuta();

    bool precisaFabrica() const override;
    bool executa(Simulador& sim, std::istringstream& args) override;
    std::string getAjuda() const override;

private:
    bool estaEmCurso(const std::string& nomeFicheiro) const;

    // Um ficheiro pode executar outro, mas nao um que ainda esteja a meio (senao nunca mais acabava):
    // guardam-se os nomes dos ficheiros a meio, num array de tamanho fixo
    inline static const int maxEmCurso = 10;
    std::string emCurso[maxEmCurso];
    int numEmCurso;
};

#endif //COMANDOEXECUTA_H
