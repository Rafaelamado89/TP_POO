//
// Created by Rafael on 06/11/2026.
//

#ifndef ECRA_H
#define ECRA_H

#include "Settings.h"
#include <string>

class Ecra {
    public:
      Ecra(int linhas, int colunas);

      int getLinhas() const { return linhas; }
      int getColunas() const { return colunas; }
      void limpa();
      void mostra() const;
      void moldura(int linha, int coluna, int altura, int largura);
      void posiciona(int linha, int coluna);
      void escreve(char c);
      void escreve(const std::string& texto);
      void escreve(int linha, int coluna, char c);
      void escreve(int linha, int coluna, const std::string& texto);

    void regua(int linha, int coluna, int linhasGrelha, int colunasGrelha);

private:
    static const int MAX_LINHAS = Settings::ecra_max_linhas;
    static const int MAX_COLUNAS = Settings::ecra_max_colunas;

    char Buffer[MAX_LINHAS][MAX_COLUNAS];


    int linhas, colunas;

    int cursorL;
    int cursorC;




};



#endif //ECRA_H
