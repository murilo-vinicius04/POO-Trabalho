#include "Quiz.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <cstring>

void Quiz::modoIndividual() {
    cout << "Bem-vindo ao Modo Individual! Digite seu nome: ";
    string nome;
    cin >> nome;

    Jogador jogador(nome);
    cout << "Boa sorte, " << jogador.nome << "! O jogo vai começar!\n";

    int nivelAtual = 1;
    int acertosConsecutivos = 0;
    int proximaPerguntaEspecial = 100;

    while (true) {
        if (jogador.pontuacao >= proximaPerguntaEspecial) {
            cout << "Você desbloqueou uma pergunta especial! Escolha sua categoria favorita.\n";
            cout << "Categorias disponíveis:\n";
            
            vector<string> categorias = {"Música", "História", "Ciência", "Geografia", "Esportes"};
            for (size_t i = 0; i < categorias.size(); ++i) {
                cout << i + 1 << ". " << categorias[i] << "\n";
            }
            int categoriaEscolhida;
            cin >> categoriaEscolhida;
            string categoria = categorias[categoriaEscolhida - 1];

            Pergunta pergunta = sortearPerguntaPorCategoria(5, categoria); // Pergunta especial de nível 5
            exibirPergunta(pergunta);

            cout << "Escolha uma opção:\n";
            cout << "1. Responder\n";
            cout << "2. Sair do jogo\n";
            int escolha;
            cin >> escolha;

            if (escolha == 1) {
                cout << "Digite sua resposta (A, B, C, D): ";
                char resposta;
                cin >> resposta;
                resposta = toupper(resposta);

                if (resposta == pergunta.resposta) {
                    cout << "Parabéns, você acertou a pergunta especial!\n";
                    jogador.pontuacao += 80;
                } else {
                    cout << "Que pena, você errou a pergunta especial. Resposta correta era " << pergunta.resposta << ".\n";
                }
                cout << "Pontuação atual: " << jogador.pontuacao << "\n";
            } else if (escolha == 2) {
                cout << "Você escolheu sair. Pontuação final: " << jogador.pontuacao << "\n";
                salvarPontuacao(jogador);
                return;
            } else {
                cout << "Opção inválida.\n";
            }

            proximaPerguntaEspecial += 200; 
        }

        Pergunta pergunta = sortearPergunta(nivelAtual); 
        cout << "Pergunta ID: " << pergunta.id << endl; 

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

                if (resposta == pergunta.resposta) {
                    cout << "Parabéns, você acertou!\n";
                    jogador.pontuacao += nivelAtual * 10;
                    acertosConsecutivos++;
                    if (acertosConsecutivos >= 5 && nivelAtual < 4) {
                        nivelAtual++;
                        acertosConsecutivos = 0;
                    }
                } else {
                    cout << "Que pena, você errou. Resposta correta era " << pergunta.resposta << ".\n";
                    salvarPontuacao(jogador);
                    cout << "Pontuação final: " << jogador.pontuacao << "\n";
                    cout << "Recordes do Ranking:\n";
                    exibirRanking();
                    return;
                }
                cout << "Pontuação atual: " << jogador.pontuacao << "\n";
                break;
            } else if (escolha == 2) {
                if (jogador.excluirAlternativas > 0) {
                    excluirAlternativas(pergunta);
                    jogador.excluirAlternativas--;
                    cout << "Ajudas restantes - Excluir Alternativas: " << jogador.excluirAlternativas << "\n";
                } else {
                    cout << "Ajuda não disponível: Excluir duas alternativas.\n";
                }
            } else if (escolha == 3) {
                if (jogador.pular > 0) {
                    cout << "Você escolheu pular a pergunta.\n";
                    jogador.pular--;
                    cout << "Ajudas restantes - Pular: " << jogador.pular << "\n";
                    break; 
                } else {
                    cout << "Ajuda não disponível: Pular a pergunta.\n";
                }
            } else if (escolha == 4) {
                if (jogador.dica > 0) {
                    cout << "Dica: " << pergunta.dica << "\n";
                    jogador.dica--;
                    cout << "Ajudas restantes - Dica: " << jogador.dica << "\n";
                } else {
                    cout << "Ajuda não disponível: Dica.\n";
                }
            } else if (escolha == 5) {
                cout << "Você escolheu sair. Pontuação final: " << jogador.pontuacao << "\n";
                salvarPontuacao(jogador);
                return;
            } else {
                cout << "Opção inválida.\n";
            }
        }
    }

    cout << "Pontuação final: " << jogador.pontuacao << "\n";
    cout << "Recordes do Ranking:\n";
    exibirRanking();
}

bool Quiz::perguntaJaFeita(int id) {
    return find(perguntasFeitas.begin(), perguntasFeitas.end(), id) != perguntasFeitas.end();
}

Pergunta Quiz::sortearPergunta(int nivel) {
    srand(time(0));
    vector<Pergunta> perguntasNivel;
    for (const auto& pergunta : perguntas) {
        if (pergunta.nivel == nivel && !perguntaJaFeita(pergunta.id)) {
            perguntasNivel.push_back(pergunta);
        }
    }
    cout << "Perguntas disponíveis para o nível " << nivel << ": " << perguntasNivel.size() << endl; // Debug
    if (perguntasNivel.empty()) {
        cerr << "Nenhuma pergunta disponível para o nível " << nivel << ".\n";
        exit(1); // 
    }
    int indice = rand() % perguntasNivel.size();
    perguntasFeitas.push_back(perguntasNivel[indice].id);
    cout << "Perguntas feitas: "; // Debug: Imprimir vetor de perguntasFeitas
    for (int id : perguntasFeitas) {
        cout << id << " ";
    }
    cout << endl;
    return perguntasNivel[indice];
}

Pergunta Quiz::sortearPerguntaPorCategoria(int nivel, const string& categoria) {
    srand(time(0));
    vector<Pergunta> perguntasNivelCategoria;
    for (const auto& pergunta : perguntas) {
        if (pergunta.nivel == nivel && pergunta.categoria == categoria && !perguntaJaFeita(pergunta.id)) {
            perguntasNivelCategoria.push_back(pergunta);
        }
    }
    if (perguntasNivelCategoria.empty()) {
        cerr << "Nenhuma pergunta disponível para o nível " << nivel << " e categoria " << categoria << ".\n";
        exit(1); // Termina o programa com erro
    }
    int indice = rand() % perguntasNivelCategoria.size();
    perguntasFeitas.push_back(perguntasNivelCategoria[indice].id);
    cout << "Perguntas feitas: "; // Debug: Imprimir vetor de perguntasFeitas
    for (int id : perguntasFeitas) {
        cout << id << " ";
    }
    cout << endl;
    return perguntasNivelCategoria[indice];
}

void Quiz::exibirPergunta(const Pergunta& pergunta) {
    cout << "Nível: " << pergunta.nivel << "\n";
    cout << "Pergunta: " << pergunta.enunciado << endl;
    for (size_t i = 0; i < pergunta.opcoes.size(); ++i) {
        cout << char('A' + i) << ": " << pergunta.opcoes[i] << endl;
    }
}

void Quiz::salvarPontuacao(const Jogador& jogador) {
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
        nome = nome.substr(0, nome.size() - 1); // Remove the comma at the end

        if (strcmp(nome.c_str(), jogador.nome.c_str()) == 0) {
            encontrado = true;
            if (jogador.pontuacao > pontuacao) {
                arquivoEscrita << "Nome: " << jogador.nome << ", Pontuação: " << jogador.pontuacao << endl;
            } else {
                arquivoEscrita << linha << endl;
            }
        } else {
            arquivoEscrita << linha << endl;
        }
    }

    if (!encontrado) {
        arquivoEscrita << "Nome: " << jogador.nome << ", Pontuação: " << jogador.pontuacao << endl;
    }

    arquivoLeitura.close();
    arquivoEscrita.close();

    remove("pontuacoes.txt");
    rename("pontuacoes_temp.txt", "pontuacoes.txt");
}

void Quiz::excluirAlternativas(Pergunta& pergunta) {
    vector<int> erradas;
    int indiceCorreto = pergunta.resposta - 'A'; // Obter o índice da resposta correta
    for (int i = 0; i < 4; i++) {
        if (i != indiceCorreto) {
            erradas.push_back(i); // Adicionar índices das opções incorretas
        }
    }
    // Embaralhar e selecionar duas alternativas incorretas para remover
    random_shuffle(erradas.begin(), erradas.end());
    erradas.resize(2);

    for (int idx : erradas) {
        pergunta.opcoes[idx] = ""; // Esconder as opções removidas
    }
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
        getline(ss, dica, ';'); // Pode estar vazio

        int id = stoi(idStr);
        int nivel = stoi(nivelStr);
        vector<string> opcoes = {opcaoA, opcaoB, opcaoC, opcaoD};
        perguntas.emplace_back(id, nivel, categoria, enunciado, opcoes, resposta[0], dica);

        // Debug: Print the details of the loaded question
        cout << "Carregada pergunta ID: " << id << ", Nível: " << nivel << ", Categoria: " << categoria << endl;
    }

    arquivo.close();
}