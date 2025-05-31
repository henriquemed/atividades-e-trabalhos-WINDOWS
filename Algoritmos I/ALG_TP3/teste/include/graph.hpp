
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Graph {
    private:
        vector<vector<int>> adj;  // matriz de adjacência que representa a região

    public:
        vector<string> city_names; // lista de nomes das cidades na mesma ordem em que aparecem em "adj"

        int n_vertices; // número de vértices no grafo

        // construtor da classe Graph. 
        // preenche "n_vertices" e inicializa "adj"
        Graph(int vertices);

        // adiciona à matriz uma aresta com distance de from para to
        void addRoad(int from, int to, int distance);

        // adiciona uma cidade ao vetor city_names
        void addCity(string name);

        // verifica se a cidade já foi adicionada ao vetor city_names.
        // se sim, retorna seu lugar no vetor (isso corresponde ao lugar na matriz)
        int cityAdded(string name);

        // verifica a existência de uma estrada de from para to e retorna sua distância.
        // lembrete: distância 0 significa que não há estrada
        int hasRoad(int from, int to);

        // retorna uma cópia da matriz de adjacência
        vector<vector<int>> getMatrix ();
};

#endif
