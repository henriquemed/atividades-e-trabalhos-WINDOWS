#include "greedy.hpp"
#include <vector>

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
            int road_cost = g.hasRoad(current, i);
            if (road_cost > 0 && road_cost < min_cost && !visited[i]) {
                min_cost = road_cost;
                next = i;
            }
        }

        if (next == -1) { // não há mais vértices para visitar
            bool all_visited = true;
            for (bool v : visited) {
                if (!v) {
                    all_visited = false;
                    break;
                }
            }

            if (all_visited) { // se todos foram visitados, tenta voltar ao início
                int return_cost = g.hasRoad(current, 0);
                if (return_cost > 0) {
                    cost += return_cost;
                    path.push_back(0);
                    if (cost < best_cost) {
                        best_path = path;
                        best_cost = cost;
                    }
                }
            } else if (path.size() > 1) { // backtracking
                int last = path.back();
                path.pop_back();
                visited[last] = false;
                cost -= g.hasRoad(path.back(), last);
                current = path.back();

                // tenta o segundo menor caminho
                int second_next = -1, second_min = 99999;
                for (int i = 0; i < n; i++) {
                    int road_cost = g.hasRoad(current, i);
                    if (road_cost > 0 && road_cost < second_min && !visited[i] && i != last) {
                        second_min = road_cost;
                        second_next = i;
                    }
                }

                if (second_next != -1) { // se encontrou um caminho alternativo
                    visited[second_next] = true;
                    path.push_back(second_next);
                    cost += g.hasRoad(current, second_next);
                    current = second_next;
                    continue;
                }
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