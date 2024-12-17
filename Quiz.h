#ifndef QUIZ_H
#define QUIZ_H

#include <iostream>
#include <vector>
#include "Pergunta.h"
#include "Jogador.h"
using namespace std;

class Quiz {
public:
    // Modo Individual do jogo
    void modoIndividual();

    // Carrega as perguntas a partir de um arquivo
    void carregarPerguntas(const string& arquivoNome);

    // Exibe as regras do modo individual para o jogador
    void exibirRegrasModoIndividual();

private:
    // Sorteia uma pergunta com base no nível de dificuldade
    Pergunta sortearPergunta(int nivel);

    // Sorteia uma pergunta de um determinado nível e categoria, para as perguntas especiais
    Pergunta sortearPerguntaPorCategoria(int nivel, const string& categoria);

    // Exibe uma pergunta e suas alternativas
    void exibirPergunta(const Pergunta& pergunta);

    // Salva a pontuação do usuário no arquivo de ranking
    void salvarPontuacao(const Usuario& usuario);

    // Remove duas alternativas incorretas da pergunta
    void excluirAlternativas(Pergunta& pergunta);

    // Exibe o ranking a partir do arquivo de pontuações
    void exibirRanking();

    vector<Pergunta> perguntas; 
};

#endif // QUIZ_H