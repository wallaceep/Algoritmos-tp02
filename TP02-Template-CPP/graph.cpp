#include "graph.hpp"
#include <limits.h>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

#define INF 0x3f3f3f3f

// Construtor do grafo
Graph::Graph(int U, int J){
    this->numV = U + J;
    adjList.resize(numV);
    graph.resize(numV+2);
    indexV = 0;
    indexE = 0;
}

// Adiciona os vértices e as arestas referentes na lista de adj
void Graph::addEdge(string &userName, string &jobName){
    // verifica se o userName ja foi adicinado antes de adicionar
    // caso não, adiciona o vértice e mapeia ele
    if (input.find(userName) == input.end()) {
        input[userName] = indexV;
        indexV++;
    }

    // verifica se o jobName ja foi adicinado antes de adicionar
    // caso não, adiciona o vértice e mapeia ele
    if (input.find(jobName) == input.end()) {
        input[jobName] = indexV;
        indexV++;
    }

    // obtem os indices 
    int userIndex = input[userName];
    int jobIndex = input[jobName];

    // salva na lista de adjacencia 
    adjList[userIndex].push_back(jobIndex);
}

// Adiciona os vértices e as arestas com capacidade referentes na lista de adj 
void Graph::addEdgeExactly(string &userName, string &jobName){
    // verifica se o userName ja foi adicinado antes de adicionar
    // caso não, adiciona o vértice e mapeia ele
    if (inputE.find(userName) == inputE.end()) {
        inputE[userName] = indexE;
        indexE++;
    } 

    // verifica se o jobName ja foi adicinado antes de adicionar
    // caso não, adiciona o vértice e mapeia ele
    if (inputE.find(jobName) == inputE.end()) {
        inputE[jobName] = indexE;
        indexE++;
    } 

    // obtem os indices
    int userIndex = inputE[userName];
    int jobIndex = inputE[jobName];

    // adiciona as arestas com capacidade
    Edge forwardEdge = {userIndex, jobIndex, 1, 0};
    Edge backwardEdge = {jobIndex, userIndex, 0, 0};

    // constroi a lista de adj
    graph[userIndex].push_back(forwardEdge);
    graph[jobIndex].push_back(backwardEdge);
}

// verifica se o vertice ja foi adicionado antes de liga-lo com o sink e o source
bool Graph::verify(string name){
    if (inputE.find(name) == inputE.end())
        return false;
    return true;
}

// algoritmo guloso
int Graph::greedyAlgorithm(){
    vector<int> matchings;
    int num = adjList.size();

    for (int i = 0; i < num; i++) {
        std::vector<int> adj_list = adjList[i];
        std::sort(adj_list.begin(), adj_list.end());
        int n_list = adj_list.size();
        
        for (int j = 0; j < n_list; j++) {
            // Seleciona o trabalho atualmente avaliado
            int selected = adj_list[j];
             // Verifica se o trabalho já foi atribuído a outro usuário
            // Se não tiver sido atribuído, adiciona a correspondência (usuário -> trabalho)
            if (find(matchings.begin(), matchings.end(), selected) == matchings.end()) {
                matchings.push_back(selected);
                break;
            }
        }
    }
    // Retorna o número total de correspondências (usuário -> trabalho)
    return matchings.size();
}

bool Graph::dfs(int u, int sink, vector<bool>& visited) {
    // Se chegou ao destino, retorna a capacidade mínima encontrada ao longo do caminho
    if (u == sink) {
        return true;
    }

    visited[u] = true;

    // Explora todas as arestas saindo do vértice u
    for (Edge& edge : graph[u]) {
        int v = edge.job;
        int resudualCapacity = edge.capacity - edge.flow;

        // Verifica se a aresta não foi visitada e ainda tem capacidade residual
        if (!visited[v] && resudualCapacity > 0) {
            // Se foi possível encontrar um caminho aumentante
            if (dfs(v, sink, visited)) {
                // Atualiza o fluxo na aresta atual
                edge.flow = 1;
                // Atualiza o fluxo na aresta reversa (aresta residual)
                for (Edge& reverseEdge : graph[v]) {
                    if (reverseEdge.job == u) {
                        reverseEdge.capacity = 1;
                        reverseEdge.flow = 0;
                        break;
                    }
                }

                return true;
            }
        }
    }

    return false;
}

// Algoritmo de Ford-Fulkerson
int Graph::fordFulkerson() {
    int source = inputE["source"];
    int sink = inputE["sink"];
    int maxFlow = 0;

    // Executa a DFS enquanto houver caminhos aumentantes
    while (true) {
        vector<bool> visited(graph.size(), false);

        // Encontra um caminho aumentante usando a DFS
        bool pathExist = dfs(source, sink, visited);
        // Se não há mais caminhos aumentantes, termina o loop
        if (!pathExist) {
            break;
        }

        // Adiciona o fluxo do caminho aumentante ao fluxo máximo
        maxFlow++;
    }

    return maxFlow;
}