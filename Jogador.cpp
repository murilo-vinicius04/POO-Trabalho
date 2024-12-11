#include "Jogador.h"
#include <iostream>

using namespace std;

ostream& operator<<(ostream& os, const Jogador& jogador) {
    os << "Nome: " << jogador.getNome() << ", Pontuação: " << jogador.getPontuacao();
    return os;
}

Jogador& operator+=(Jogador& jogador, int pontos) {
    jogador.setPontuacao(jogador.getPontuacao() + pontos);
    return jogador;
}