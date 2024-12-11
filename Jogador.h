#ifndef JOGADOR_H
#define JOGADOR_H

#include <string>
#include <map>
using namespace std;

class Jogador {
public:
    string nome;
    int pontuacao;
    int excluirAlternativas;
    int dica;
    int pular;

    Jogador(string n, int excluirAlt = 1, int d = 2, int p = 1) 
        : nome(n), pontuacao(0), excluirAlternativas(excluirAlt), dica(d), pular(p) {
        // ...existing code...
    }
};

#endif // JOGADOR_H