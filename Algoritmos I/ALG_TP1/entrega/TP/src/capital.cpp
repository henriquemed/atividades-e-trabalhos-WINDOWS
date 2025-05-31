#include "capital.hpp"

std::vector<int> bfs(const std::vector<std::vector<bool>>& matrix, int start_node) {
    int n = matrix.size();
    std::vector<int> distances(n, 999); // distância padrão: 999
    std::queue<int> q;

    distances[start_node] = 0;
    q.push(start_node);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int neighbor = 0; neighbor < n; ++neighbor) {
            if (matrix[current][neighbor] && distances[neighbor] == 999) { // nós ainda não visitados
                distances[neighbor] = distances[current] + 1;
                q.push(neighbor);
            }
        }
    }
    return distances;
}

int ShortestPathsVertex (const vector<vector<bool>>& matrix) {
    int n = matrix.size();
    int minVertex = -1;
    int minSum = INT_MAX;

    for (int i = 0; i < n; ++i) {
        vector<int> distances = bfs(matrix, i);
        int sum = 0;

        // Verifica se todos os vértices são alcançáveis
        bool allReachable = true;
        for (int d : distances) {
            if (d == INT_MAX) {
                allReachable = false;
                break;
            }
            sum += d;
        }

        // Atualiza o vértice com menor somatório de caminhos
        if (allReachable && sum < minSum) {
            minSum = sum;
            minVertex = i;
        }
    }
    return minVertex;
}

void printDistances (vector<int>& distances, int start_node) {
    cout << "distances from node " << start_node << endl;
    for (int distance : distances) {
        cout << distance << endl;
    }
}

int sumDistances(vector<int>& distances) {
    int sum = 0;
    for (size_t i = 0; i < distances.size(); i++) {
        sum += distances[i];
    }
    return sum;
}
