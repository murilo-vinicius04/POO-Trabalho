#include "Quiz.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <cstring>
#include <unordered_set>

void Quiz::modoIndividual() {
    cout << "Bem-vindo ao Modo Individual! Digite seu nome: ";
    string nome;
    cin >> nome;

    Jogador jogador(nome);
    Usuario* usuario = &jogador;
    cout << "Boa sorte, " << usuario->obterNome() << "! O jogo vai começar!\n";

    int nivelAtual = 1;
    int acertosConsecutivos = 0;
    int proximaPerguntaEspecial = 100;
    unordered_set<int> perguntasJaFeitas;

    while (true) {
        if (jogador.getPontuacao() >= proximaPerguntaEspecial) {
            cout << "Você desbloqueou uma pergunta especial! Escolha sua categoria favorita.\n";
            cout << "Categorias disponíveis:\n";
            vector<string> categorias = {"Música", "História", "Ciência", "Geografia", "Esportes"};
            for (size_t i = 0; i < categorias.size(); ++i) {
                cout << i + 1 << ". " << categorias[i] << "\n";
            }
            int categoriaEscolhida;
            cin >> categoriaEscolhida;
            string categoria = categorias[categoriaEscolhida - 1];

            Pergunta pergunta = sortearPerguntaPorCategoria(5, categoria);
            exibirPergunta(pergunta);

            cout << "Escolha uma opção:\n";
            cout << "1. Responder\n";
            cout << "5. Sair do jogo\n";
            int escolha;
            cin >> escolha;

            if (escolha == 1) {
                cout << "Digite sua resposta (A, B, C, D): ";
                char resposta;
                cin >> resposta;
                resposta = toupper(resposta);

                if (resposta == pergunta.getResposta()) {
                    cout << "Parabéns, você acertou a pergunta especial!\n";
                    jogador += 80;
                } else {
                    cout << "Que pena, você errou a pergunta especial. Resposta correta era " << pergunta.getResposta() << ".\n";
                }
                cout << "Pontuação atual: " << jogador << "\n";
            } else if (escolha == 5) {
                cout << "Você escolheu sair. Pontuação final: " << jogador << "\n";
                salvarPontuacao(jogador);
                return;
            } else {
                cout << "Opção inválida.\n";
            }

            proximaPerguntaEspecial += 200;
        }

        Pergunta pergunta = sortearPergunta(nivelAtual);

        while (perguntasJaFeitas.find(pergunta.getId()) != perguntasJaFeitas.end()) {
            pergunta = sortearPergunta(nivelAtual);
        }
        perguntasJaFeitas.insert(pergunta.getId());

        while (true) {
            exibirPergunta(pergunta);

            cout << "Escolha uma opção:\n";
            cout << "1. Responder\n";
            cout << "2. Usar Ajuda: Excluir duas alternativas\n";
            cout << "3. Usar Ajuda: Pular a pergunta\n";
            cout << "4. Usar Ajuda: Dica\n";
            cout << "5. Sair do jogo\n";
            int escolha;
            cin >> escolha;

            if (escolha == 1) {
                cout << "Digite sua resposta (A, B, C, D): ";
                char resposta;
                cin >> resposta;
                resposta = toupper(resposta);

                if (resposta == pergunta.getResposta()) {
                    cout << "Parabéns, você acertou!\n";
                    jogador += nivelAtual * 10;
                    acertosConsecutivos++;
                    if (acertosConsecutivos >= 3 && nivelAtual < 4) {
                        nivelAtual++;
                        acertosConsecutivos = 0;
                    }
                } else {
                    cout << "Que pena, você errou. Resposta correta era " << pergunta.getResposta() << ".\n";
                    salvarPontuacao(jogador);
                    cout << "Pontuação final: " << jogador << "\n";
                    cout << "Recordes do Ranking:\n";
                    exibirRanking();
                    return;
                }
                cout << "Pontuação atual: " << jogador << "\n";
                break;
            } else if (escolha == 2) {
                if (jogador.getExcluirAlternativas() > 0) {
                    excluirAlternativas(pergunta);
                    jogador.setExcluirAlternativas(jogador.getExcluirAlternativas() - 1);
                    cout << "Ajuda disponível - Excluir Alternativas: " << jogador.getExcluirAlternativas() << "\n";
                    exibirPergunta(pergunta);
                } else {
                    cout << "Ajuda não disponível: Excluir duas alternativas.\n";
                }
            } else if (escolha == 3) {
                if (jogador.getPular() > 0) {
                    cout << "Você escolheu pular a pergunta.\n";
                    jogador.setPular(jogador.getPular() - 1);
                    cout << "Ajuda disponível - Pular: " << jogador.getPular() << "\n";
                    break;
                } else {
                    cout << "Ajuda não disponível: Pular a pergunta.\n";
                }
            } else if (escolha == 4) {
                if (jogador.getDica() > 0) {
                    cout << "Dica: " << pergunta.getDica() << "\n";
                    jogador.setDica(jogador.getDica() - 1);
                    cout << "Ajuda disponível - Dica: " << jogador.getDica() << "\n";
                } else {
                    cout << "Ajuda não disponível: Dica.\n";
                }
            } else if (escolha == 5) {
                cout << "Você escolheu sair. Pontuação final: " << jogador << "\n";
                salvarPontuacao(jogador);
                return;
            } else {
                cout << "Opção inválida.\n";
            }
        }
    }

    cout << "Pontuação final: " << jogador << "\n";
    cout << "Recordes do Ranking:\n";
    exibirRanking();
}

Pergunta Quiz::sortearPergunta(int nivel) {
    srand(time(0));
    vector<Pergunta> perguntasNivel;
    for (const auto& pergunta : perguntas) {
        if (pergunta.getNivel() == nivel) {
            perguntasNivel.push_back(pergunta);
        }
    }
    if (perguntasNivel.empty()) {
        cerr << "Nenhuma pergunta disponível para o nível " << nivel << ".\n";
        exit(1);
    }
    int indice = rand() % perguntasNivel.size();
    return perguntasNivel[indice];
}

Pergunta Quiz::sortearPerguntaPorCategoria(int nivel, const string& categoria) {
    srand(time(0));
    vector<Pergunta> perguntasNivelCategoria;
    for (const auto& pergunta : perguntas) {
        if (pergunta.getNivel() == nivel && pergunta.getCategoria() == categoria) {
            perguntasNivelCategoria.push_back(pergunta);
        }
    }
    if (perguntasNivelCategoria.empty()) {
        cerr << "Nenhuma pergunta disponível para o nível " << nivel << " e categoria " << categoria << ".\n";
        exit(1);
    }
    int indice = rand() % perguntasNivelCategoria.size();
    return perguntasNivelCategoria[indice];
}

void Quiz::exibirPergunta(const Pergunta& pergunta) {
    cout << "Nível: " << pergunta.getNivel() << "\n";
    cout << "Pergunta: " << pergunta.getEnunciado() << endl;
    vector<string> opcoes = pergunta.getOpcoes();
    for (size_t i = 0; i < opcoes.size(); ++i) {
        cout << char('A' + i) << ": " << opcoes[i] << endl;
    }
}

void Quiz::salvarPontuacao(const Usuario& usuario) {
    ifstream arquivoLeitura("pontuacoes.txt");
    ofstream arquivoEscrita("pontuacoes_temp.txt");
    bool encontrado = false;

    if (!arquivoLeitura.is_open() || !arquivoEscrita.is_open()) {
        cerr << "Não foi possível abrir o arquivo de pontuações." << endl;
        return;
    }

    string linha;
    while (getline(arquivoLeitura, linha)) {
        stringstream ss(linha);
        string label, nome, pontuacaoStr;
        int pontuacao;

        ss >> label >> nome >> pontuacaoStr >> pontuacao;
        nome = nome.substr(0, nome.size() - 1);

        if (strcmp(nome.c_str(), usuario.obterNome().c_str()) == 0) {
            encontrado = true;
            if (usuario.getPontuacao() > pontuacao) {
                arquivoEscrita << "Nome: " << usuario.obterNome() << ", Pontuação: " << usuario.getPontuacao() << endl;
            } else {
                arquivoEscrita << linha << endl;
            }
        } else {
            arquivoEscrita << linha << endl;
        }
    }

    if (!encontrado) {
        arquivoEscrita << "Nome: " << usuario.obterNome() << ", Pontuação: " << usuario.getPontuacao() << endl;
    }

    arquivoLeitura.close();
    arquivoEscrita.close();

    remove("pontuacoes.txt");
    rename("pontuacoes_temp.txt", "pontuacoes.txt");
}

void Quiz::excluirAlternativas(Pergunta& pergunta) {
    vector<int> erradas;
    int indiceCorreto = pergunta.getResposta() - 'A';
    for (int i = 0; i < 4; i++) {
        if (i != indiceCorreto) {
            erradas.push_back(i);
        }
    }
    random_shuffle(erradas.begin(), erradas.end());
    erradas.resize(2);

    vector<string> opcoes = pergunta.getOpcoes();
    for (int i : erradas) {
        opcoes[i] = "";
    }
    pergunta.setOpcoes(opcoes);
    cout << "Duas opções incorretas foram removidas.\n";
}

void Quiz::exibirRanking() {
    ifstream arquivo("pontuacoes.txt");
    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo de pontuações.\n";
        return;
    }

    cout << "\n==== RANKING ====\n";
    string linha;
    while (getline(arquivo, linha)) {
        cout << linha << "\n";
    }
    arquivo.close();
    cout << "==================\n";
}

void Quiz::carregarPerguntas(const string& arquivoNome) {
    ifstream arquivo(arquivoNome);
    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo de perguntas.\n";
        return;
    }

    string linha;
    while (getline(arquivo, linha)) {
        stringstream ss(linha);
        string idStr, nivelStr, categoria, enunciado, opcaoA, opcaoB, opcaoC, opcaoD, resposta, dica;
        getline(ss, idStr, ';');
        getline(ss, nivelStr, ';');
        getline(ss, categoria, ';');
        getline(ss, enunciado, ';');
        getline(ss, opcaoA, ';');
        getline(ss, opcaoB, ';');
        getline(ss, opcaoC, ';');
        getline(ss, opcaoD, ';');
        getline(ss, resposta, ';');
        getline(ss, dica, ';');

        int id = stoi(idStr);
        int nivel = stoi(nivelStr);
        vector<string> opcoes = {opcaoA, opcaoB, opcaoC, opcaoD};
        perguntas.emplace_back(id, nivel, categoria, enunciado, opcoes, resposta[0], dica);
    }

    arquivo.close();
}