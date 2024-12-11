#include <iostream>
#include "Pergunta.h"
#include "Jogador.h"
#include "Quiz.h"

int main() {
    Quiz quiz;
    quiz.carregarPerguntas("perguntas.txt"); // Ensure this path is correct

    int modo;
    cout << "Selecione o modo de jogo:\n1. Modo Individual\n2. Modo 1vs1\n";
    cin >> modo;

    if (modo == 1) {
        quiz.modoIndividual();
    } else if (modo == 2) {
        // Implementar modo 1vs1
    } else {
        cout << "Modo inválido!" << endl;
    }

    return 0;
}