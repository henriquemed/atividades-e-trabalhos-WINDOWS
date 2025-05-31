#include "greedy.hpp"

using namespace std;

vector<int> returnSmallestPath(Graph g) {
    int n = g.n_vertices;
    vector<int> best_path;
    int best_cost = 99999;

    vector<int> path = {0}; // começa no vértice 0
    vector<bool> visited(n, false);
    visited[0] = true;
    int current = 0, cost = 0;

    while (true) {
        int next = -1, min_cost = 99999;

        // encontra o próximo vértice com a menor estrada
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                int road_cost = g.hasRoad(current, i);
                if (road_cost < min_cost) {
                    min_cost = road_cost;
                    next = i;
                }
            }
        }

        if (next == -1) { // não há mais vértices para visitar
            // volta ao início para completar o ciclo e somar ao custo total
            int return_cost = g.hasRoad(current, 0);
            cost += return_cost;
            path.push_back(0);

            if (cost < best_cost) {
                best_path = path;
                best_cost = cost;
            }
            break;
        }

        // segue para o próximo vértice
        visited[next] = true;
        path.push_back(next);
        cost += g.hasRoad(current, next);
        current = next;
    }

    if (!best_path.empty()) best_path.push_back(best_cost); // adiciona o custo ao final
    return best_path;
}

// NOTA: isso era muito mais complexo e contava com backtracking para prevenir casos onde
// o caminho não retornava ao vértice inicial, mas mudei após a mensagem do monitor.

// "Para facilitar o desenvolvimento do TP3, todas as entradas serão definidas como um grafo 
// completo, similar a estrutura dos exemplos na especificação."