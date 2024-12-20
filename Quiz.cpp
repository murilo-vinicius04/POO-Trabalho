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

    // Criação de um objeto Jogador com nome fornecido pelo usuário
    Jogador jogador(nome);
    Usuario* usuario = &jogador;
    cout << "Boa sorte, " << usuario->obterNome() << "! O jogo vai começar!\n";

    int nivelAtual = 1;
    int acertosConsecutivos = 0; // Contador para controlar aumento de nível após 3 acertos
    int proximaPerguntaEspecial = 100; // Pontuação em que se libera uma pergunta especial
    unordered_set<int> perguntasJaFeitas; // Conjunto para armazenar IDs de perguntas já respondidas

    // Loop principal do jogo.
    while (true) {
        // Verifica se o jogador atingiu a pontuação para pergunta especial
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

            // Sorteia uma pergunta especial do nível 5 e da categoria escolhida
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

        // Garante que a pergunta ainda não foi feita anteriormente
        while (perguntasJaFeitas.find(pergunta.getId()) != perguntasJaFeitas.end()) {
            pergunta = sortearPergunta(nivelAtual);
        }
        perguntasJaFeitas.insert(pergunta.getId());

        // Loop interno para manipular a pergunta atual, permitindo uso de ajudas
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
                // Jogador escolhe responder
                cout << "Digite sua resposta (A, B, C, D): ";
                char resposta;
                cin >> resposta;
                resposta = toupper(resposta);

                // Checa se a resposta está correta
                if (resposta == pergunta.getResposta()) {
                    cout << "Parabéns, você acertou!\n";
                    // Pontuação baseada no nível: nívelAtual * 10 pontos
                    jogador += nivelAtual * 10;
                    acertosConsecutivos++;
                    // Se acertar 3 vezes seguidas, aumenta o nível até o nível 4
                    if (acertosConsecutivos >= 3 && nivelAtual < 4) {
                        nivelAtual++;
                        acertosConsecutivos = 0;
                    }
                } else {
                    // Caso erre, o jogo termina e a pontuação é salva
                    cout << "Que pena, você errou. Resposta correta era " << pergunta.getResposta() << ".\n";
                    salvarPontuacao(jogador);
                    cout << "Pontuação final: " << jogador << "\n";
                    cout << "Recordes do Ranking:\n";
                    exibirRanking();
                    return;
                }
                cout << "Pontuação atual: " << jogador << "\n";
                break; // Sai do loop interno e parte para a próxima pergunta
            } else if (escolha == 2) {
                // Usa ajuda para excluir duas alternativas, se ainda houver disponibilidade
                if (jogador.getExcluirAlternativas() > 0) {
                    excluirAlternativas(pergunta);
                    jogador.setExcluirAlternativas(jogador.getExcluirAlternativas() - 1);
                    cout << "Ajuda disponível - Excluir Alternativas: " << jogador.getExcluirAlternativas() << "\n";
                    // Exibe a pergunta com as alternativas removidas
                    exibirPergunta(pergunta);
                } else {
                    cout << "Ajuda não disponível: Excluir duas alternativas.\n";
                }
            } else if (escolha == 3) {
                // Ajuda para pular pergunta
                if (jogador.getPular() > 0) {
                    cout << "Você escolheu pular a pergunta.\n";
                    jogador.setPular(jogador.getPular() - 1);
                    cout << "Ajuda disponível - Pular: " << jogador.getPular() << "\n";
                    break;
                } else {
                    cout << "Ajuda não disponível: Pular a pergunta.\n";
                }
            } else if (escolha == 4) {
                // Ajuda de dica
                if (jogador.getDica() > 0) {
                    cout << "Dica: " << pergunta.getDica() << "\n";
                    jogador.setDica(jogador.getDica() - 1);
                    cout << "Ajuda disponível - Dica: " << jogador.getDica() << "\n";
                } else {
                    cout << "Ajuda não disponível: Dica.\n";
                }
            } else if (escolha == 5) {
                // Sair do jogo, salva a pontuação e finaliza
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
    // Filtra as perguntas de um determinado nível
    vector<Pergunta> perguntasNivel;
    for (const auto& pergunta : perguntas) {
        if (pergunta.getNivel() == nivel) {
            perguntasNivel.push_back(pergunta);
        }
    }
    // Se não houver perguntas do nível solicitado, encerra o jogo
    if (perguntasNivel.empty()) {
        cerr << "Nenhuma pergunta disponível para o nível " << nivel << ".\n";
        exit(1);
    }
    // Sorteia um índice aleatório do vetor de perguntas daquele nível
    int indice = rand() % perguntasNivel.size();
    return perguntasNivel[indice];
}

Pergunta Quiz::sortearPerguntaPorCategoria(int nivel, const string& categoria) {
    srand(time(0));
    // Filtra as perguntas por nível e categoria
    vector<Pergunta> perguntasNivelCategoria;
    for (const auto& pergunta : perguntas) {
        if (pergunta.getNivel() == nivel && pergunta.getCategoria() == categoria) {
            perguntasNivelCategoria.push_back(pergunta);
        }
    }
    // Se não houver perguntas da categoria e nível especificados, encerra o jogo
    if (perguntasNivelCategoria.empty()) {
        cerr << "Nenhuma pergunta disponível para o nível " << nivel << " e categoria " << categoria << ".\n";
        exit(1);
    }
    // Escolhe uma pergunta aleatória dentre as filtradas
    int indice = rand() % perguntasNivelCategoria.size();
    return perguntasNivelCategoria[indice];
}

void Quiz::exibirPergunta(const Pergunta& pergunta) {
    // Mostra o nível e o enunciado da pergunta
    cout << "Nível: " << pergunta.getNivel() << "\n";
    cout << "Pergunta: " << pergunta.getEnunciado() << endl;
    vector<string> opcoes = pergunta.getOpcoes();
    // Exibe as alternativas disponíveis (A, B, C, D), caso a alternativa não tenha sido removida
    for (size_t i = 0; i < opcoes.size(); ++i) {
        cout << char('A' + i) << ": " << opcoes[i] << endl;
    }
}

void Quiz::salvarPontuacao(const Usuario& usuario) {
    /* Lê o arquivo de pontuações existente e grava um novo arquivo temporário
       atualizando a pontuação do usuário se for maior que a anterior. */
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

        // Compara o nome do usuário atual com a linha do arquivo
        if (strcmp(nome.c_str(), usuario.obterNome().c_str()) == 0) {
            encontrado = true;
            // Se a nova pontuação for maior, atualiza
            if (usuario.getPontuacao() > pontuacao) {
                arquivoEscrita << "Nome: " << usuario.obterNome() << ", Pontuação: " << usuario.getPontuacao() << endl;
            } else {
                // Caso contrário, mantém a pontuação antiga
                arquivoEscrita << linha << endl;
            }
        } else {
            arquivoEscrita << linha << endl;
        }
    }

    // Se não encontrou o jogador no arquivo, adiciona-o agora
    if (!encontrado) {
        arquivoEscrita << "Nome: " << usuario.obterNome() << ", Pontuação: " << usuario.getPontuacao() << endl;
    }

    arquivoLeitura.close();
    arquivoEscrita.close();

    // Remove o arquivo antigo e renomeia o temporário, efetivando as alterações
    remove("pontuacoes.txt");
    rename("pontuacoes_temp.txt", "pontuacoes.txt");
}

// Seleciona duas alternativas incorretas e as remove do display
void Quiz::excluirAlternativas(Pergunta& pergunta) {
    vector<int> erradas;
    int indiceCorreto = pergunta.getResposta() - 'A';
    for (int i = 0; i < 4; i++) {
        if (i != indiceCorreto) {
            erradas.push_back(i);
        }
    }
    // Embaralha as alternativas erradas e seleciona duas
    random_shuffle(erradas.begin(), erradas.end());
    erradas.resize(2);

    vector<string> opcoes = pergunta.getOpcoes();
    // Substitui as opções erradas selecionadas por strings vazias
    for (int i : erradas) {
        opcoes[i] = "";
    }
    pergunta.setOpcoes(opcoes);
    cout << "Duas opções incorretas foram removidas.\n";
}

void Quiz::exibirRanking() {
    // Lê o arquivo de pontuações e exibe todas as pontuações salvas
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
    // Carrega perguntas a partir de um arquivo texto no formato CSV com separador ';'
    ifstream arquivo(arquivoNome);
    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo de perguntas.\n";
        return;
    }

    string linha;
    while (getline(arquivo, linha)) {
        stringstream ss(linha);
        string idStr, nivelStr, categoria, enunciado, opcaoA, opcaoB, opcaoC, opcaoD, resposta, dica;
        // Lê os campos separados por ponto e vírgula
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
        // Cria objeto Pergunta e insere no vetor perguntas
        perguntas.emplace_back(id, nivel, categoria, enunciado, opcoes, resposta[0], dica);
    }

    arquivo.close();
}

void Quiz::exibirRegrasModoIndividual() {
    // Exibe ao jogador as regras do modo individual antes do jogo começar
    cout << "\n=== Regras do Modo Individual ===\n";
    cout << "1. Objetivo: Responda perguntas e acumule pontos.\n";
    cout << "   Perguntas mais difíceis valem mais pontos.\n";
    cout << "2. Dificuldade Crescente: O jogo começa no nível 1 e\n";
    cout << "   as perguntas ficam mais difíceis à medida que você avança.\n";
    cout << "3. Perguntas Especiais: Em momentos especiais, você\n";
    cout << "   terá a chance de responder a uma pergunta única e desafiadora.\n";
    cout << "   - Escolha uma categoria favorita.\n";
    cout << "   - Prepare-se para essas perguntas!\n";
    cout << "   - Não há ajudas disponíveis para perguntas especiais.\n";
    cout << "4. Ajudas Disponíveis:\n";
    cout << "   - Excluir duas alternativas: Remove duas respostas incorretas (1 vez por jogo).\n";
    cout << "   - Pular pergunta: Avança para a próxima pergunta sem perder pontos (1 vez por jogo).\n";
    cout << "   - Dica: Receba uma dica útil (2 vezes por jogo).\n";
    cout << "5. Fim do Jogo: O jogo termina se você errar uma resposta.\n";
    cout << "   - Sua pontuação final será salva no ranking, se for uma das melhores.\n";
    cout << "6. Ranking: O ranking com as melhores pontuações será exibido ao final.\n";
    cout << "=================================\n\n";
}