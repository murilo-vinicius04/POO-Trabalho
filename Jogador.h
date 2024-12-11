#ifndef JOGADOR_H
#define JOGADOR_H

#include <string>
#include <map>
#include "Usuario.h"
using namespace std;

class Jogador : public Usuario {
private:
    string nome;
    int pontuacao;
    int excluirAlternativas;
    int dica;
    int pular;

public:
    Jogador(const string& _nome, int _excluirAlternativas = 1, int _dica = 2, int _pular = 1) 
        : nome(_nome), pontuacao(0), excluirAlternativas(_excluirAlternativas), dica(_dica), pular(_pular) {}

    Jogador(const Jogador& other)
        : nome(other.nome), pontuacao(other.pontuacao), excluirAlternativas(other.excluirAlternativas),
          dica(other.dica), pular(other.pular) {}

    ~Jogador() {}

    string getNome() const { return nome; }
    void setNome(const string& n) { nome = n; }
    int getPontuacao() const override { return pontuacao; }
    void setPontuacao(int p) { pontuacao = p; }
    int getExcluirAlternativas() const { return excluirAlternativas; }
    void setExcluirAlternativas(int val) { excluirAlternativas = val; }
    int getDica() const { return dica; }
    void setDica(int val) { dica = val; }
    int getPular() const { return pular; }
    void setPular(int val) { pular = val; }

    void atualizarPontuacao(int pontos) override {
        pontuacao += pontos;
    }

    string obterNome() const override {
        return nome;
    }
};

ostream& operator<<(ostream& os, const Jogador& jogador);

Jogador& operator+=(Jogador& jogador, int pontos);

#endif // JOGADOR_H