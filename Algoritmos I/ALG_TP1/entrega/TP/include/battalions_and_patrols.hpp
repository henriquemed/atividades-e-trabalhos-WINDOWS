#ifndef BATTALIONS_AND_PATROLS_HPP
#define BATTALIONS_AND_PATROLS_HPP

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// roda DFS e preenche a pilha com a ordem de término
void dfsOrder(const vector<vector<bool>>& adj, int node, vector<bool>& visited, stack<int>& order);

// roda DFS no grafo transposto e encontra um SCC
void dfsSCC(const vector<vector<bool>>& adj, int node, vector<bool>& visited, vector<bool>& scc);

// transpoe a matriz de adjacência
vector<vector<bool>> transposeGraph(const vector<vector<bool>>& adj);

// algoritmo de Kosaraju
vector<vector<int>> kosaraju(const vector<vector<bool>>& adj, int startNode);


#endif