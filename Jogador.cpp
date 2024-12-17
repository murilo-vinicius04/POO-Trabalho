#include "Jogador.h"
#include <iostream>

using namespace std;

// Operador de inserção sobrecarregado para imprimir as informações do jogador
ostream& operator<<(ostream& os, const Jogador& jogador) {
    os << "Nome: " << jogador.getNome() << ", Pontuação: " << jogador.getPontuacao();
    return os;
}

// Operador de adição composto sobrecarregado para facilitar a adição de pontos
Jogador& operator+=(Jogador& jogador, int pontos) {
    jogador.setPontuacao(jogador.getPontuacao() + pontos);
    return jogador;
}