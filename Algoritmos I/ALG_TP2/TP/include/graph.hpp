#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <tuple>

using namespace std;

struct Edge {
    
    int to;
    int capacity;
    int flow;

    Edge(int t, int c) {
        to = t;
        capacity = c;
        flow = 0;
    }
};



class Graph {
private:
    int V;
    vector<vector<Edge>> adj;
    vector<int> demand;

    vector<int> generator_list;

    // roda a bfs. retorna true se houver um caminho da fonte 's' até a sink 't'
    // retorna false se não alcançar
    bool bfs(vector<int>& parent);

public:

    // construtor do grafo (da classe)
    Graph(int vertices);

    // adiciona uma aresta direta com capacity de from para to e uma aresta 
    // reversa com capacidade 0 para representar o fluxo residual
    void addEdge(int from, int to, int capacity);

    // define demanda
    void setDemand(int node, int d);

    // calcula o fluxo máximo (energia total) do grafo usando Edmonds-Karp
    int calculateMaxFlow();

    // verifica se o id informado é de um gerador
    // true se for, false se não
    bool isGenerator (int id);

    // adiciona um gerador à lista de geradores
    void addGenerator (int id);

    // acha conexões críticas (P-critical) e as ordena pela capacidade, depois origem, depois destino
    vector<tuple<int, int, int>> findCriticalConnections();

};

#endif