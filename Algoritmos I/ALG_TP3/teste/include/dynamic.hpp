#ifndef DYNAMIC_HPP
#define DYNAMIC_HPP

#include "graph.hpp"
#include <vector>
#include <string>
#include <map>

using namespace std;

const int INF = 1000000000;    // constante auxiliar com um valor grande o suficiente

// parte recursiva auxiliar do problema do caixeiro viajante (TSP, Travelling Salesman Problem) 
// com programação dinâmica e bitmasking para otimizar a busca por caminhos.
// explora todas as possíveis combinações de cidades visitadas, armazenando os resultados 
// parciais em sub_results para evitar recomputações e minimizar o tempo de execução.
// 
// retorna o custo mínimo de uma viagem começando em "pos", visita todas as outras cidades
// exatamente uma vez e retorna à cidade inicial 
int tsp(int mask, int pos, vector<vector<int>> &dist, vector<vector<int>> &dp, int n);

// resolve o problema do caixeiro-viajante utilizando programação dinâmica com bitmasking. 
// encontra o caminho mais curto para visitar todas as cidades e retorna a cidade inicial, 
// armazenando a sequência de cidades visitadas e o custo total da viagem em um vetor único
// de inteiros no formato "A B C D ... A COST" onde A B C D são os índices das  cidades
// 
// em resumo, função principal que resolve o TSP usando a função tsp recursiva
vector<int> solveTSPDynamic(Graph &g);

#endif