#include <iostream>
#include "graph.hpp"
#include "brute.hpp"
#include "dynamic.hpp"
#include "greedy.hpp"

using namespace std;

int main () {

// ENTRADAS

    char strategy;
    cin >> strategy;

    int n_cities, n_roads;
    cin >> n_cities >> n_roads;

    Graph g(n_cities);  // instancia o grafo

    string city_A, city_B;
    int distance;
    for (int i=0; i < n_roads; i++) {
        cin >> city_A >> city_B >> distance;
        // adiciona/verifica cidades no vetor antes de adicionar estrada
        if (g.cityAdded(city_A) == -1) g.addCity(city_A);
        if (g.cityAdded(city_B) == -1) g.addCity(city_B);
        // adiciona estrada A para B e B para A
        g.addRoad(g.cityAdded(city_A), g.cityAdded(city_B), distance);
        g.addRoad(g.cityAdded(city_B), g.cityAdded(city_A), distance);
    }

// FORÇA BRUTA
    
    if (strategy == 'b') {
        // gera um vetor inicial com os índices das cidades
        vector<int> starter_vector = generateStarterVector(n_cities);
        // gera um vetor com todas as permutações de cidades
        vector<vector<int>> permutations = generatePermutationsVector(starter_vector);
        // calcula o menor caminho dentre as permutações.
        // retorna o primeiro resultado que gera o menor caminho
        vector<int> smallest_path = returnSmallestPath(permutations, g);
        // imprime o resultado
        printResult(smallest_path, g);
    }
    
// PROGRAMAÇÃO DINÂMICA

    else if (strategy == 'd') {
        // resolve o problema do caixeiro viajante usando programação dinâmica, bitmasking e recursão
        vector<int> smallest_path = solveTSPDynamic(g);
        // imprime o resultado
        printResult(smallest_path, g);
    }

// ALGORITMO GULOSO
    
    else if (strategy == 'g') {
        // percorre a matriz de adjacência que representa a região, buscando o menor caminho
        // local na esperança que isso leve a uma solução ótima global.
        vector<int> smallest_path = returnSmallestPath(g);
        // imprime o resultado
        printResult(smallest_path, g);
    }

// NENHUMA DAS OPÇÕES

    else cout << "Insert a valid option for strategy." << endl;

    return 0;
}
