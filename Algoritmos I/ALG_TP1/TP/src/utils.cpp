#include "utils.hpp"

int cityAdded (string city_name, vector<string>& city_array) {
    for (int i=0; i < static_cast<int>(city_array.size()); i++) {
        if (city_array[i] == city_name) return i;
    }
    return -1;
}

void printCityArray (string * city_array, int n_cities) {
    for (int i=0; i < n_cities; i++) {
        cout << city_array[i] << endl;
    }
}

int minElementId(vector<int>& vector) {
    int min_id = 0;
    for (int i = 1; i < static_cast<int>(vector.size()); ++i) {
        if (vector[i] < vector[min_id]) {
            min_id = i;
        }
    }
    return min_id;
}

/*

PRINTAR SCCS

    for (int i = 0; i < SCCs.size(); ++i) {
        for (int j = 0; j < SCCs[i].size(); ++j) {
            cout << SCCs[i][j] << " "
        }
        cout << endl;
    }

PRINTAR CIDADES

    printCityArray(cidades, n_cidades);

PRINTAR GRAFO

    grafo.print_graph();

*/
