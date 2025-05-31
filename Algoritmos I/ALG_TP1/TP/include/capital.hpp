#ifndef CAPITAL_HPP
#define CAPITAL_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// roda a BFS e calcula menores caminhos
// retorna um vetor com as distâncias do vértice inicial aos outros
vector<int> bfs (const vector<vector<bool>>& matrix, int start_node);

// retorna vertice com menor soma de caminhos
int ShortestPathsVertex (const vector<vector<bool>>& matrix);

// printa todas os valores de distância do vertice inicial aos outros
void printDistances (vector<int>& distances, int start_node);

// soma as distancias do vertice inicial aos outros
int sumDistances(vector<int>& distances);

#endif