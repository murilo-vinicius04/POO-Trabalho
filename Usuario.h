#ifndef USUARIO_H
#define USUARIO_H

#include <string>
using namespace std;

class Usuario {
public:
    virtual void atualizarPontuacao(int pontos) = 0;

    // Retorna o nome do usuário
    virtual string obterNome() const = 0;

    // Retorna a pontuação do usuário
    virtual int getPontuacao() const = 0;

    // Destrutor virtual para garantir polimorfismo
    virtual ~Usuario() = default;
};

#endif // USUARIO_H