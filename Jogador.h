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
    Jogador(string n, int excluirAlt = 1, int d = 2, int p = 1) 
        : nome(n), pontuacao(0), excluirAlternativas(excluirAlt), dica(d), pular(p) {}

    // Construtor de cópia
    Jogador(const Jogador& other)
        : nome(other.nome), pontuacao(other.pontuacao), excluirAlternativas(other.excluirAlternativas),
          dica(other.dica), pular(other.pular) {}

    // Destrutor
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

    // Sobrecarga do operador <<
    friend ostream& operator<<(ostream& os, const Jogador& jogador) {
        os << "Nome: " << jogador.obterNome() << ", Pontuação: " << jogador.getPontuacao();
        return os;
    }

    // Sobrecarga do operador +
    Jogador operator+(const Jogador& outro) const {
        Jogador novoJogador(this->nome + " & " + outro.nome);
        novoJogador.setPontuacao(this->pontuacao + outro.pontuacao);
        return novoJogador;
    }
};

#endif // JOGADOR_H