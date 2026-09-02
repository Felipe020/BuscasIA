#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <algorithm>
using namespace std;

void imprimeTabuleiro(const vector<char>& t) {
    cout << t[0] << " " << t[1] << " " << t[2] << "\n";
    cout << t[3] << " " << t[4] << " " << t[5] << "\n";
    cout << t[6] << " " << t[7] << " " << t[8] << "\n";
    cout << "------\n";
}

void busca()
{
    vector<char> tabuleiroInicio = {'B', 'V', 'B', 'V', 'V', 'V', 'P', 'V', 'P'}; // Estado inicial
    vector<char> tabuleiroFinal = {'P', 'V', 'P', 'V', 'V', 'V', 'B', 'V', 'B'};  // Estado final
    vector<char> tabuleiroAtual;

    bool sucesso = false;
    bool fracasso = false;

    stack<vector<char>> caminho;
    set<vector<char>> visitados;

    // Mapeamento dos movimentos válidos
    vector<vector<int>> adj = {
        {5, 7}, {6, 8}, {3, 7}, {2, 8}, {}, {0, 6}, {1, 5}, {0, 2}, {1, 3}};

    caminho.push(tabuleiroInicio);
    visitados.insert(tabuleiroInicio);

   while(!sucesso && !fracasso){
        if(caminho.empty()){
            fracasso = true;
            break;
        }

        vector<char> tabuleiroAtual = caminho.top();

        if(tabuleiroAtual == tabuleiroFinal){
            sucesso = true;
            break;
        }
        
        bool encontrouNovoEstado = false;

        for(int i = 0; i < 9; ++i){
            if(tabuleiroAtual[i] != 'V'){ 
                for(int vizinho : adj[i]){ 
                    if(tabuleiroAtual[vizinho] == 'V'){ 
                        
                        vector<char> novoEstado = tabuleiroAtual;
                        swap(novoEstado[i], novoEstado[vizinho]); // Faz o movimento
                        
                        if(visitados.find(novoEstado) == visitados.end()){
                            caminho.push(novoEstado); 
                            visitados.insert(novoEstado);
                            encontrouNovoEstado = true;
                            break;
                        }
                    }
                }
            }
            if(encontrouNovoEstado) break;
        }
        
        // Se não houver movimentos válidos e não visitados a partir deste estado
        if(!encontrouNovoEstado){
            caminho.pop(); // Backtracking: Remove o nó atual e volta para N := pai(N)
        }
    }

   if(sucesso){
        cout << "Solucao encontrada usando Backtracking!\n";
        cout << "Quantidade de passos: " << caminho.size() - 1 << "\n\n";

        // Extrai a sequência da pilha (sai do fim para o início)
        vector<vector<char>> sequenciaFinal;
        while(!caminho.empty()){
            sequenciaFinal.push_back(caminho.top());
            caminho.pop();
        }
        
        // Inverte para imprimir na ordem cronológica
        reverse(sequenciaFinal.begin(), sequenciaFinal.end());

        // Imprime cada passo
        for(size_t i = 0; i < sequenciaFinal.size(); ++i){
            cout << "Passo " << i << ":\n";
            imprimeTabuleiro(sequenciaFinal[i]);
        }
        
    } else {
        cout << "Nenhuma solucao possivel." << endl;
    }
}

int main()
{
    busca();
    return 0;
}

