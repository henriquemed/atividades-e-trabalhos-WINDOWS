#include "brute.hpp"

vector<int> generateStarterVector (int n_cities) {
    vector<int> starter_vector; // esse vetor representa todas as cidades (em índices)
    for (int i=0; i < n_cities; i++) starter_vector.push_back(i);
    return starter_vector;
}

void permute(vector<int>& nums, int start, vector<vector<int>>& result) {
    if (start == static_cast<int>(nums.size()) - 1) {
        result.push_back(nums);
        return;
    }
    for (int i = start; i < static_cast<int>(nums.size()); ++i) {
        swap(nums[start], nums[i]);
        permute(nums, start + 1, result);
        swap(nums[start], nums[i]);
    }
}

vector<vector<int>> generatePermutationsVector(vector<int> starter_vector) {
    vector<vector<int>> permutations;
    permute(starter_vector, 0, permutations);
    return permutations;
}

vector<int> returnSmallestPath (vector<vector<int>> permutations, Graph g) {
    if (static_cast<int>(permutations.size()) == 0) {
        cerr << "Error: permutations vector is empty." << endl;
        exit(1);
    }
    
    vector<int> smallest_path;
    int smallest_cost = 99999; // o menor custo começa com o maior valor possível

    for (int i=0; i < static_cast<int>(permutations.size()); i++) {
        int starter_city = permutations[i][0];
        permutations[i].push_back(starter_city); // adiciona a cidade inicial ao final do caminho
        
        int path_cost = 0;
        bool path_is_valid = true;
        for (int j=0; j < static_cast<int>(permutations[i].size())-1; j++) {
            int from_city = permutations[i][j];
            int to_city = permutations[i][j+1];
            path_cost += g.hasRoad(from_city, to_city);
            if (g.hasRoad(from_city, to_city) == 0) path_is_valid = false; 
            // se não há alguma das estradas, o caminho não é mais válido
        }
        
        if (path_is_valid && path_cost < smallest_cost) {
            permutations[i].push_back(path_cost);
            smallest_path = permutations[i];
            smallest_cost = path_cost;
        }
    }

    return smallest_path;
}

void printResult(vector<int> resulting_path, Graph g) {
    int vector_size = static_cast<int>(resulting_path.size());

    // imprime o custo do caminho (último elemento do vetor)
    cout << resulting_path[vector_size - 1] << endl;

    // imprime o caminho ignorando o penúltimo elemento (retorno à primeira cidade)
    for (int i = 0; i < vector_size - 2; i++) {
        cout << g.city_names[resulting_path[i]] << " ";
    }
    cout << endl;
}
