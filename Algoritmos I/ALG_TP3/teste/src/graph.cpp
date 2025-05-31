#include "graph.hpp"

Graph::Graph(int vertices) {
    n_vertices = vertices;
    adj.resize(n_vertices, vector<int>(n_vertices, 0));  // usa vetor de vetores para matriz de adjacência
}

void Graph::addRoad(int from, int to, int distance) {
    adj[from][to] = distance;
}

// adiciona uma cidade ao vetor city_names
void Graph::addCity(string name) {
    city_names.emplace_back(name);
}

int Graph::cityAdded(string name) {
    for (int i = 0; i < static_cast<int>(city_names.size()); i++) {
        if (city_names[i] == name) {
            return i;
        }
    }
    return -1;  // cidade não encontrada
}

int Graph::hasRoad(int from, int to) {
    return adj[from][to];
}

vector<vector<int>> Graph::getMatrix () {
    return adj;
}