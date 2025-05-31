#ifndef GREEDY_HPP
#define GREEDY_HPP

#include "graph.hpp"
#include <vector>

using namespace std;

// GREEDY ALGORITHM

// percorre uma vez a matriz de adjacência que representa a região, buscando 
// o menor caminho local na esperança que isso leve a uma solução ótima global.
// como os grafos de entrada sempre são completos, não é necessário se preocupar 
// em não encontrar um caminho válido.
// 
// retorna o menor caminho encontrado através desse método (greedy algorithm)
vector<int> returnSmallestPath(Graph g);

#endif