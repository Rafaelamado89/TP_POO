//
// Created by Rafael on 06/11/2026.
//

#include "Ecra.h"
#include <iostream>

using namespace std;

Ecra::Ecra(int linhas, int colunas) :
    cursorL(0), cursorC(0) {
  if (linhas < 1) linhas = 1;
  if (linhas > MAX_LINHAS) linhas = MAX_LINHAS;
  if (colunas < 1) colunas = 1;
  if (colunas > MAX_COLUNAS) colunas = MAX_COLUNAS;
  this->linhas = linhas;
  this->colunas = colunas;
  limpa();
}

void Ecra::limpa() {
  for(int i = 0; i < linhas; i++) {
    for(int j = 0; j < colunas; j++) {
      Buffer[i][j] = ' ';
    }
  }
  cursorL = 0;
  cursorC = 0;
}

void Ecra::mostra() const {
  for(int i = 0; i < linhas; i++) {
    for(int j = 0; j < colunas; j++) {
      cout << Buffer[i][j];
    }
    cout << endl;
  }
}

void Ecra::posiciona(int linha, int coluna) {
  cursorL = linha;
  cursorC = coluna;
}

void Ecra::escreve(char c) {
  // Ignora fora dos limites
  if (cursorL < 0 || cursorL >= linhas || cursorC < 0 || cursorC >= colunas) {
    cursorC++;
    return;
  }
  Buffer[cursorL][cursorC] = c;
  cursorC++;
}

void Ecra::escreve(const std::string& texto) {
  for(char c : texto) {
    escreve(c);
  }
}

void Ecra::escreve(int linha, int coluna, char c) {
  posiciona(linha, coluna);
  escreve(c);
}

void Ecra::escreve(int linha, int coluna, const string& texto) {
  posiciona(linha, coluna);
  escreve(texto);
}

void Ecra::moldura(int linha, int coluna, int altura, int largura) {
  if (altura < 1 || largura < 1) return;

  int ultL = linha + altura - 1;
  int ultC = coluna + largura - 1;

  // bordas horizontais
  for (int j = coluna; j <= ultC; j++) {
    posiciona(linha, j);
    escreve('-');
    posiciona(ultL, j);
    escreve('-');
  }
  // bordas verticais
  for (int i = linha; i <= ultL; i++) {
    posiciona(i, coluna);
    escreve('|');
    posiciona(i, ultC);
    escreve('|');
}
  // cantos
  posiciona(linha, coluna);
  escreve('+');
  posiciona(linha, ultC);
  escreve('+');
  posiciona(ultL, coluna);
  escreve('+');
  posiciona(ultL, ultC);
  escreve('+');
}


void Ecra::regua(int linha, int coluna, int nLinhas, int nColunas) {
  // regua horizontal
  posiciona(linha, coluna + 1);
  for (int j = 0; j < nColunas; j++)
    escreve(char('A' + (j % 26)));

  // regua vertical
  for (int i = 0; i < nLinhas; i++) {
    posiciona(linha + 1 + i, coluna);
    escreve(char('A' + (i % 26)));
  }
}