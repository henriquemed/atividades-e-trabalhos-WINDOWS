#ifndef DYNAMIC_HPP
#define DYNAMIC_HPP

#include "graph.hpp"

using namespace std;

// DYNAMIC PROGRAMMING

// nó a ser usado pela árvore
struct Node {

    vector <int> sons;  // vetor de filhos
    vector <int> path;  // caminho até esse nó
    int path_cost;      // custo do caminho
    bool visited;       // esse nó foi visitado?
    bool root;          // esse nó é a raiz?

};

// função auxiliar que faz uma busca em profundidade (depth-first search) para construir os caminhos válidos.
// preenche os nodes de toda a árvore.
void dfs(int current, vector<int> path, int cost, vector<vector<int>>& tree, Graph& g, vector<bool>& visited, int root);

// função auxiliar de buildPossibilityTrees.
// constrói UMA árvore de possibilidades a partir de uma cidade raiz em forma de lista de adjacência e a retorna
vector<vector<int>> buildTree (int root, Graph g);

// retorna um vetor com uma árvore de possibilidades para cada cidade inicial
vector<vector<vector<int>>> buildPossibilityTrees (int n_cities, Graph g);

// navega pelo vetor de árvores seleciona o caminho de menor custo dentre os possíveis
// 
// LEMBRETE: exemplo de caminho: 0 1 2 3 0 95
// ou seja, inicia em 0, por exemplo, e termina em 0, e após o último vértice temos o custo
vector<int> returnSmallestPath(vector<vector<vector<int>>> tree_vector);

#endif