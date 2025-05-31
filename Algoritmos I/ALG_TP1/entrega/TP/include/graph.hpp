#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <iostream>

using namespace std;

class Graph {

    private:

        int n_nodes_;
        vector<vector<bool>> matrix_;   // matriz de adjacência

    public:
        
        // construtor (inicializador)
        Graph(int n_nodes);

        // destrutor
        ~Graph();
        
        // verifica se os valores estão dentro do intervalo permitido (maior que zero e menor que o total)
        bool rangeIsValid (int node_id);

        // adiciona uma aresta que vai de from_node para to_node
        void addEdge(int from_node, int to_node);

        // verifica se há uma aresta que vai de from_node para to_node
        bool hasEdge(int from_node, int to_node);

        // retorna uma referência pra matriz de adjacência que representa esse grafo
        vector<vector<bool>>& getMatrix ();

        // retorna uma cópia da matriz de adjac~encia que representa esse grafo
        vector<vector<bool>> getMatrixbyCopy ();

        // imprime o grafo todo
        void print_graph();

};

#endif
