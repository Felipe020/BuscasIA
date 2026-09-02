#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

void imprimeTabuleiro(const vector<char> &t)
{
    cout << t[0] << " " << t[1] << " " << t[2] << "\n";
    cout << t[3] << " " << t[4] << " " << t[5] << "\n";
    cout << t[6] << " " << t[7] << " " << t[8] << "\n";
    cout << "------\n";
}

// Função de Backtracking
void backtracking(
    const vector<char> &tabuleiroAtual,
    const vector<char> &tabuleiroFinal,
    const vector<vector<int>> &adj,
    vector<vector<char>> &caminhoAtual,
    vector<vector<char>> &melhorCaminho,
    set<vector<char>> &visitados)
{
    // Se chegou ao estado final
    if (tabuleiroAtual == tabuleiroFinal)
    {

        // Verifica se é a primeira solução
        // ou se encontrou uma solução melhor
        if (melhorCaminho.empty() ||
            caminhoAtual.size() < melhorCaminho.size())
        {

            melhorCaminho = caminhoAtual;
        }

        return;
    }

    // Se o caminho atual já é maior ou igual à melhor solução,
    // não há motivo para continuar explorando
    if (!melhorCaminho.empty() &&
        caminhoAtual.size() >= melhorCaminho.size())
    {
        return;
    }

    // Percorre todas as casas do tabuleiro
    for (int i = 0; i < 9; ++i)
    {

        // Se existe um cavalo nessa posição
        if (tabuleiroAtual[i] != 'V')
        {
            // Percorre os movimentos possíveis do cavalo
            for (int vizinho : adj[i])
            {
                // O movimento só pode ser feito para uma casa vazia
                if (tabuleiroAtual[vizinho] == 'V')
                {
                    // Cria o novo estado
                    vector<char> novoEstado = tabuleiroAtual;

                    // Faz o movimento do cavalo
                    swap(novoEstado[i], novoEstado[vizinho]);

                    // Verifica se o estado ainda não está no caminho atual
                    if (visitados.find(novoEstado) == visitados.end())
                    {
                        // Marca o estado como visitado
                        visitados.insert(novoEstado);

                        // Adiciona o estado ao caminho atual
                        caminhoAtual.push_back(novoEstado);

                        // Continua a busca
                        backtracking(
                            novoEstado,
                            tabuleiroFinal,
                            adj,
                            caminhoAtual,
                            melhorCaminho,
                            visitados);

                        // remove o estado do caminho
                        caminhoAtual.pop_back();

                        // Desmarca o estado para permitir
                        // que outro caminho possa utilizá-lo
                        visitados.erase(novoEstado);
                    }
                }
            }
        }
    }
}

void busca()
{
    // Estado inicial
    vector<char> tabuleiroInicio = {
        'B', 'V', 'B',
        'V', 'V', 'V',
        'P', 'V', 'P'};

    // Estado final
    vector<char> tabuleiroFinal = {
        'P', 'V', 'P',
        'V', 'V', 'V',
        'B', 'V', 'B'};

    
    vector<vector<int>> adj = {
        {5, 7}, 
        {6, 8}, 
        {3, 7}, 
        {2, 8}, 
        {},     
        {0, 6}, 
        {1, 5}, 
        {0, 2}, 
        {1, 3}  
    };

    // Caminho que está sendo explorado
    vector<vector<char>> caminhoAtual;

    // Melhor caminho encontrado
    vector<vector<char>> melhorCaminho;

    // Estados visitados no caminho atual
    set<vector<char>> visitados;

    // Estado inicial entra no caminho
    caminhoAtual.push_back(tabuleiroInicio);

    // Marca o estado inicial
    visitados.insert(tabuleiroInicio);

    // Inicia o Backtracking
    backtracking(
        tabuleiroInicio,
        tabuleiroFinal,
        adj,
        caminhoAtual,
        melhorCaminho,
        visitados);

    if (!melhorCaminho.empty())
    {

        cout << "Solucao encontrada usando Backtracking!\n";

        cout << "Quantidade de passos: "
             << melhorCaminho.size() - 1
             << "\n\n";

        // Mostra todos os estados da solução
        for (size_t i = 0; i < melhorCaminho.size(); ++i)
        {

            cout << "Passo " << i << ":\n";

            imprimeTabuleiro(melhorCaminho[i]);
        }
    }
    else
    {
        cout << "Nenhuma solucao possivel." << endl;
    }
}

int main()
{
    busca();
    return 0;
}