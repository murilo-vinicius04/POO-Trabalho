#ifndef PERGUNTA_H
#define PERGUNTA_H

#include <string>
#include <vector>
using namespace std;

class Pergunta {
private:
    int id;
    int nivel;
    string categoria;
    string enunciado;
    vector<string> opcoes;
    char resposta;
    string dica;

public:
    Pergunta(int _id, int _nivel, string _categoria, string _enunciado, vector<string> _opcoes, char _resposta, string _dica = "")
        : id(_id), nivel(_nivel), categoria(_categoria), enunciado(_enunciado), opcoes(_opcoes), resposta(toupper(_resposta)), dica(_dica) {}

    // Construtor de cópia
    Pergunta(const Pergunta& other)
        : id(other.id), nivel(other.nivel), categoria(other.categoria), enunciado(other.enunciado),
          opcoes(other.opcoes), resposta(other.resposta), dica(other.dica) {}

    // Destrutor
    ~Pergunta() {}

    int getId() const { return id; }
    void setId(int i) { id = i; }

    int getNivel() const { return nivel; }
    void setNivel(int n) { nivel = n; }

    string getCategoria() const { return categoria; }
    void setCategoria(const string& c) { categoria = c; }

    string getEnunciado() const { return enunciado; }
    void setEnunciado(const string& e) { enunciado = e; }

    vector<string> getOpcoes() const { return opcoes; }
    void setOpcoes(const vector<string>& o) { opcoes = o; }

    char getResposta() const { return resposta; }
    void setResposta(char r) { resposta = toupper(r); }

    string getDica() const { return dica; }
    void setDica(const string& d) { dica = d; }

    void atualizarOpcoes(const vector<string>& novasOpcoes) { opcoes = novasOpcoes; }
};

#endif // PERGUNTA_H