// Incluindo as bibliotecas necessárias
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <fstream>

using namespace std;

// Definição da classe para representar um grafo usando Matriz de Adjacência
class GrafoMatriz {
private:
    int V;  // Número de vértices
    vector<vector<int>> matriz;  // Matriz de adjacência

public:
    // Construtor da classe
    GrafoMatriz(int V) {
        this->V = V;
        matriz.resize(V, vector<int>(V, 0)); // Inicializa a matriz com zeros
    }

    // Adiciona uma aresta ao grafo
    void addAresta(int u, int v) {
        matriz[u][v] = 1; // Atribui 1 para indicar a existência da aresta
    }

    // Função auxiliar para imprimir o caminho percorrido na BFS
    void printCaminhoBFS(int s, int t, vector<int>& parent) {
        if (t == s) {
            cout << s << " ";
            return;
        }
        printCaminhoBFS(s, parent[t], parent);
        cout << t << " ";
    }

    // Executa a Busca em Largura (BFS) a partir do vértice 's'
    void BFS(int s, int t) {
        vector<bool> visitado(V, false); // Vetor de visitados
        vector<int> parent(V, -1); // Vetor de pais
        queue<int> fila; // Fila para a BFS

        visitado[s] = true; // Marca o vértice 's' como visitado
        fila.push(s); // Adiciona 's' à fila

        while (!fila.empty()) {
            int u = fila.front(); // Obtém o primeiro vértice da fila
            fila.pop(); // Remove o primeiro vértice da fila

            for (int v = 0; v < V; v++) {
                if (matriz[u][v] && !visitado[v]) {
                    visitado[v] = true;
                    parent[v] = u;
                    fila.push(v);
                }
            }
        }

        if (!visitado[t]) {
            cout << "Não há caminho entre os vértices." << endl;
        } else {
            cout << "Caminho entre " << s << " e " << t << ": ";
            printCaminhoBFS(s, t, parent);
            cout << endl;
        }
    }

    // Função auxiliar para realizar a DFS iterativamente
    void DFS(int s, int t) {
        vector<bool> visitado(V, false); // Vetor de visitados
        stack<int> pilha; // Pilha para a DFS

        visitado[s] = true; // Marca o vértice 's' como visitado
        pilha.push(s); // Empilha 's'

        vector<int> parent(V, -1); // Vetor de pais

        while (!pilha.empty()) {
            int u = pilha.top(); // Obtém o topo da pilha
            pilha.pop(); // Remove o topo da pilha

            for (int v = 0; v < V; v++) {
                if (matriz[u][v] && !visitado[v]) {
                    visitado[v] = true;
                    parent[v] = u;
                    pilha.push(v);
                }
            }
        }

        if (!visitado[t]) {
            cout << "Não há caminho entre os vértices." << endl;
        } else {
            cout << "Caminho entre " << s << " e " << t << ": ";
            printCaminhoBFS(s, t, parent);
            cout << endl;
        }
    }
};

// Função para carregar o grafo a partir de um arquivo
void carregarGrafo(GrafoMatriz& grafoMatriz) {
    ifstream arquivo("grafo.txt");
    int V, E;
    arquivo >> V >> E;

    for (int i = 0; i < E; i++) {
        int u, v;
        arquivo >> u >> v;
        grafoMatriz.addAresta(u, v);
    }
}

int main() {
    GrafoMatriz grafoMatriz(5); // Inicializa com 5 vértices (ou o número de vértices desejado)

    carregarGrafo(grafoMatriz);

    // Teste de BFS
    grafoMatriz.BFS(0, 4);

    // Teste de DFS
    grafoMatriz.DFS(0, 4);

    return 0;
}
