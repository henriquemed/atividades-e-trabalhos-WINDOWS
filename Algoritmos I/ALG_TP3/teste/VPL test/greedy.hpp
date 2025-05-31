#ifndef GREEDY_HPP
#define GREEDY_HPP

#include "graph.hpp"

using namespace std;

// GREEDY ALGORITHM

// percorre uma vez a matriz de adjacência que representa a região, buscando 
// o menor caminho local na esperança que isso leve a uma solução ótima global.
// caso não chegue a um caminho válido, utiliza backtracking para voltar a partir do
// último e tentar uma outra alternativa pelo segundo melhor caminho possível.
// 
// retorna o menor caminho encontrado através desse método (greedy algorithm)
vector<int> returnSmallestPath(Graph g);

#endif