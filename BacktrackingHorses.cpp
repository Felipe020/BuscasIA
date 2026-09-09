//g++ BacktrackingHorses.cpp -o main
//.\main.exe 

#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

// Função auxiliar para imprimir o tabuleiro
void imprimeTabuleiro(const vector<char> &t)
{
    cout << " " << t[0] << " " << t[1] << " " << t[2] << "\n";
    cout << " " << t[3] << " " << t[4] << " " << t[5] << "\n";
    cout << " " << t[6] << " " << t[7] << " " << t[8] << "\n";
}

// Imprime todos os movimentos (operadores) legais a partir de um estado
void imprimeOperadoresDisponiveis(const vector<char> &t, const vector<vector<int>> &adj)
{
    cout << "  Operadores disponíveis: ";
    bool primeiro = true;
    for (int i = 0; i < 9; ++i)
    {
        if (t[i] != 'V')
        {
            for (int vizinho : adj[i])
            {
                if (t[vizinho] == 'V')
                {
                    if (!primeiro)
                        cout << " | ";
                    cout << "Mover " << t[i] << " de " << i << " para " << vizinho;
                    primeiro = false;
                }
            }
        }
    }
    cout << "\n";
}

// Compara dois estados para descobrir qual foi a ação tomada
void descobreOperadorEscolhido(const vector<char> &t1, const vector<char> &t2)
{
    int origem = -1, destino = -1;
    char peca = ' ';
    for (int i = 0; i < 9; ++i)
    {
        if (t1[i] != t2[i])
        {
            if (t1[i] != 'V')
            {
                origem = i;
                peca = t1[i];
            }
            else
            {
                destino = i;
            }
        }
    }
    cout << "  -> OPERADOR ESCOLHIDO: Moveu " << peca << " de " << origem << " para " << destino << "\n";
}

// Algoritmo Backtracking
void backtracking(
    const vector<char> &tabuleiroAtual,
    const vector<char> &tabuleiroFinal,
    const vector<vector<int>> &adj,
    vector<vector<char>> &caminhoAtual,
    vector<vector<char>> &melhorCaminho,
    map<vector<char>, int> &melhoresDistancias,
    long long &voltasBacktrack // Contador de retornos
)
{
    // Sucesso: chegou ao estado final
    if (tabuleiroAtual == tabuleiroFinal)
    {
        if (melhorCaminho.empty() ||
            caminhoAtual.size() < melhorCaminho.size())
        {

            melhorCaminho = caminhoAtual;
        }

        return;
    }

    // Poda: o caminho atual já não pode melhorar a solução
    if (!melhorCaminho.empty() &&
        caminhoAtual.size() >= melhorCaminho.size())
    {

        return;
    }

    for (int i = 0; i < 9; ++i)
    {
        if (tabuleiroAtual[i] != 'V')
        {
            for (int vizinho : adj[i])
            {
                if (tabuleiroAtual[vizinho] == 'V')
                {

                    vector<char> novoEstado = tabuleiroAtual;
                    swap(novoEstado[i], novoEstado[vizinho]);
                    int novaDistancia = caminhoAtual.size() + 1;

                    if (melhoresDistancias.find(novoEstado) == melhoresDistancias.end() ||
                        novaDistancia < melhoresDistancias[novoEstado])
                    {

                        melhoresDistancias[novoEstado] = novaDistancia;
                        caminhoAtual.push_back(novoEstado);

                        backtracking(novoEstado, tabuleiroFinal, adj, caminhoAtual, melhorCaminho, melhoresDistancias, voltasBacktrack);

                        // BACKTRACKING: desfaz a ação e conta a "volta"
                        caminhoAtual.pop_back();
                        voltasBacktrack++;
                    }
                }
            }
        }
    }
}

// Encapsulamento para rodar uma estratégia específica e isolada
void executarEstrategia(string nomeEstrategia, const vector<vector<int>> &adj)
{
    vector<char> tabuleiroInicio = {'B', 'V', 'B', 'V', 'V', 'V', 'P', 'V', 'P'};
    vector<char> tabuleiroFinal = {'P', 'V', 'P', 'V', 'V', 'V', 'B', 'V', 'B'};

    vector<vector<char>> caminhoAtual;
    vector<vector<char>> melhorCaminho;
    map<vector<char>, int> melhoresDistancias;
    long long voltasBacktrack = 0;

    caminhoAtual.push_back(tabuleiroInicio);
    melhoresDistancias[tabuleiroInicio] = 1;

    cout << "\n======================================================\n";
    cout << "INICIANDO BUSCA - ESTRATEGIA: " << nomeEstrategia << "\n";
    cout << "======================================================\n";

    // Executa a busca
    backtracking(tabuleiroInicio, tabuleiroFinal, adj, caminhoAtual, melhorCaminho, melhoresDistancias, voltasBacktrack);

    if (!melhorCaminho.empty())
    {
        cout << "\n[!] Solucao Otima Encontrada!\n";
        cout << "- Total de passos na solucao: " << melhorCaminho.size() - 1 << "\n";
        cout << "- Total de retornos durante o backtracking: " << voltasBacktrack << "\n\n";

        cout << "--- TRILHA DA SOLUÇÃO ÓTIMA ---\n";
        for (size_t i = 0; i < melhorCaminho.size(); ++i)
        {
            cout << "\nPasso " << i << (i == 0 ? " (Estado Inicial)" : "") << ":\n";
            imprimeTabuleiro(melhorCaminho[i]);

            // Se não for o último passo, mostramos as opções e a decisão
            if (i < melhorCaminho.size() - 1)
            {
                imprimeOperadoresDisponiveis(melhorCaminho[i], adj);
                descobreOperadorEscolhido(melhorCaminho[i], melhorCaminho[i + 1]);
            }
            else
            {
                cout << "  -> ESTADO FINAL ALCANCADO!\n";
            }
        }
    }
    else
    {
        cout << "Nenhuma solucao possivel." << endl;
    }
}

int main()
{
    // Matriz 1: Prioriza o movimento no sentido HORÁRIO do ciclo dos cavalos
    // Ciclo: 0->5->6->1->8->3->2->7->0
    vector<vector<int>> adjHorario = {
        {5, 7}, // 0
        {8, 6}, // 1
        {7, 3}, // 2
        {2, 8}, // 3
        {},     // 4
        {6, 0}, // 5
        {1, 5}, // 6
        {0, 2}, // 7
        {3, 1}  // 8
    };

    // Matriz 2: Prioriza o movimento no sentido ANTI-HORÁRIO do ciclo
    vector<vector<int>> adjAntiHorario = {
        {7, 5}, // 0
        {6, 8}, // 1
        {3, 7}, // 2
        {8, 2}, // 3
        {},     // 4
        {0, 6}, // 5
        {5, 1}, // 6
        {2, 0}, // 7
        {1, 3}  // 8
    };

    // Roda o código com as duas estratégias para comparação
    executarEstrategia("SENTIDO HORARIO", adjHorario);
    executarEstrategia("SENTIDO ANTI-HORARIO", adjAntiHorario);

    return 0;
}