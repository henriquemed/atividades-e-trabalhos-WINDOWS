#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <vector>

using namespace std;

// verifica se a cidade já está dentro do array de cidades. 
// se sim, retorna seu índice no array. se não, retorna -1 (valor simbólico)
int cityAdded (string city_name, vector<string>& city_array);

// printa o array de cidades na ordem
void printCityArray (string * city_array, int n_cities);

// retorna o id do menor elemento em um vetor de ints
int minElementId(vector<int>& vector);

#endif