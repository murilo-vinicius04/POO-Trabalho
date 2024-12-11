#ifndef USUARIO_H
#define USUARIO_H

#include <string>
using namespace std;

class Usuario {
public:
    virtual void atualizarPontuacao(int pontos) = 0;
    virtual string obterNome() const = 0;
    virtual int getPontuacao() const = 0; 
    virtual ~Usuario() = default;
};

#endif // USUARIO_H