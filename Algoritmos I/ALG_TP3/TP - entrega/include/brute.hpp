#ifndef BRUTE_HPP
#define BRUTE_HPP

#include "graph.hpp"

using namespace std;

// BRUTE FORCE

// retorna um vetor de índices das cidades.
// exemplo: com 3 cidades a função retorna {0, 1, 2}
vector<int> generateStarterVector (int n_cities);

// função auxiliar para gerar permutações recursivamente usando backtracking
void permute(vector<int>& nums, int start, vector<vector<int>>& result);

// retorna um vetor com todas as permutações de cidades.
vector<vector<int>> generatePermutationsVector(vector<int> starter_vector);

// salva a permutação que faz sentido e que tem o menor custo
// calcula o custo total do caminho, colocando-o ao final do vetor. 
// exemplo de caminho: 0 1 2 3 0 95
// 
// NOTA: fazem sentido aquelas possíveis, ou seja, se  tem estrada de todos pra 
// todos na ordem da permutação e se o último da permutação chega no primeiro
vector<int> returnSmallestPath (vector<vector<int>> permutations, Graph g);

// recebe um único caminho e o retorna pela saída padrão juntamente com seu custo
void printResult(vector<int> resulting_path, Graph g);

#endif