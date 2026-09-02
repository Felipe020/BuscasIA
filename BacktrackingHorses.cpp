#include <iostream>
#include <vector>
#include <map>

using namespace std;

void imprimeTabuleiro(const vector<char>& t) {
    cout << t[0] << " " << t[1] << " " << t[2] << "\n";
    cout << t[3] << " " << t[4] << " " << t[5] << "\n";
    cout << t[6] << " " << t[7] << " " << t[8] << "\n";
    cout << "------\n";
}

void backtracking(
    const vector<char>& tabuleiroAtual,
    const vector<char>& tabuleiroFinal,
    const vector<vector<int>>& adj,
    vector<vector<char>>& caminhoAtual,
    vector<vector<char>>& melhorCaminho,
    map<vector<char>, int>& melhoresDistancias
) {
    // Poda 1: Se já achamos uma solução, ignorar qualquer caminho que fique maior ou igual a ela
    if (!melhorCaminho.empty() && caminhoAtual.size() >= melhorCaminho.size()) {
        return;
    }

    // Poda 2: Limite de segurança (sabemos que a solução ronda os 16 passos)
    if (caminhoAtual.size() > 20) {
        return;
    }

    // Sucesso: Chegou ao estado final
    if (tabuleiroAtual == tabuleiroFinal) {
        melhorCaminho = caminhoAtual;
        return;
    }

    for (int i = 0; i < 9; ++i) {
        if (tabuleiroAtual[i] != 'V') {
            for (int vizinho : adj[i]) {
                if (tabuleiroAtual[vizinho] == 'V') {
                    
                    vector<char> novoEstado = tabuleiroAtual;
                    swap(novoEstado[i], novoEstado[vizinho]);

                    int novaDistancia = caminhoAtual.size() + 1;

                    // Só avança se o estado for inédito OU se chegamos nele por uma rota mais curta
                    if (melhoresDistancias.find(novoEstado) == melhoresDistancias.end() || 
                        novaDistancia < melhoresDistancias[novoEstado]) {
                        
                        // Grava a distância recorde para este estado
                        melhoresDistancias[novoEstado] = novaDistancia;
                        
                        caminhoAtual.push_back(novoEstado);
                        
                        backtracking(novoEstado, tabuleiroFinal, adj, caminhoAtual, melhorCaminho, melhoresDistancias);
                        
                        // BACKTRACKING: Retira a peça, mas NÃO apaga a distância do map!
                        // A memória de que passamos por aqui de forma ineficiente permanece.
                        caminhoAtual.pop_back();
                    }
                }
            }
        }
    }
}

void busca() {
    vector<char> tabuleiroInicio = {
        'B', 'V', 'B',
        'V', 'V', 'V',
        'P', 'V', 'P'
    };

    vector<char> tabuleiroFinal = {
        'P', 'V', 'P',
        'V', 'V', 'V',
        'B', 'V', 'B'
    };

    vector<vector<int>> adj = {
        {5, 7}, {6, 8}, {3, 7}, {2, 8}, {}, {0, 6}, {1, 5}, {0, 2}, {1, 3}
    };

    vector<vector<char>> caminhoAtual;
    vector<vector<char>> melhorCaminho;
    
    // Substituição do Set pelo Map
    map<vector<char>, int> melhoresDistancias; 

    caminhoAtual.push_back(tabuleiroInicio);
    melhoresDistancias[tabuleiroInicio] = 1;

    backtracking(tabuleiroInicio, tabuleiroFinal, adj, caminhoAtual, melhorCaminho, melhoresDistancias);

    if (!melhorCaminho.empty()) {
        cout << "Solucao encontrada!\n";
        cout << "Quantidade de passos: " << melhorCaminho.size() - 1 << "\n\n";

        for (size_t i = 0; i < melhorCaminho.size(); ++i) {
            cout << "Passo " << i << ":\n";
            imprimeTabuleiro(melhorCaminho[i]);
        }
    } else {
        cout << "Nenhuma solucao possivel." << endl;
    }
}

int main() {
    busca();
    return 0;
}