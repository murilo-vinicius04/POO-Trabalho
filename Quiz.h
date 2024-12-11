#ifndef QUIZ_H
#define QUIZ_H

#include <iostream>
#include <vector>
#include "Pergunta.h"
#include "Jogador.h"
using namespace std;

class Quiz {
public:
    void modoIndividual();
    void carregarPerguntas(const string& arquivoNome);
private:
    Pergunta sortearPergunta(int nivel);
    Pergunta sortearPerguntaPorCategoria(int nivel, const string& categoria);
    void exibirPergunta(const Pergunta& pergunta);
    void salvarPontuacao(const Usuario& usuario);
    void excluirAlternativas(Pergunta& pergunta);
    void exibirRanking();
    vector<Pergunta> perguntas; // Supondo que as perguntas são carregadas aqui
};

#endif // QUIZ_H