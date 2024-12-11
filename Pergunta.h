#ifndef PERGUNTA_H
#define PERGUNTA_H

#include <string>
#include <vector>
using namespace std;

class Pergunta {
public:
    int id;
    int nivel;
    string categoria;
    string enunciado;
    vector<string> opcoes;
    char resposta;
    string dica;

    Pergunta(int i, int n, const string& c, const string& e, const vector<string>& o, char r, const string& d)
        : id(i), nivel(n), categoria(c), enunciado(e), opcoes(o), resposta(r), dica(d) {}
};

#endif // PERGUNTA_H