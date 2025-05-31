#include "graph.hpp"

using namespace std;

bool Graph::bfs(vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    queue<int> q;
    q.push(0);
    parent[0] = 0;

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        for (Edge& edge : adj[cur]) {
            if (parent[edge.to] == -1 && edge.capacity - edge.flow > 0) {
                parent[edge.to] = cur;
                if (edge.to == V - 1) return true;
                q.push(edge.to);
            }
        }
    }
    return false;
}

Graph::Graph(int vertices) {
    V = vertices;
    adj = vector<vector<Edge>>(vertices);
    demand = vector<int>(vertices, 0);
}

void Graph::addEdge(int from, int to, int capacity) {
    adj[from].emplace_back(to, capacity);
    adj[to].emplace_back(from, 0); // Reverse edge
}

void Graph::setDemand(int node, int d) {
    demand[node] = d;
}

int Graph::calculateMaxFlow() {
    int maxFlow = 0;
    vector<int> parent(V);

    while (bfs(parent)) { // enquanto houver um caminho da source à sink
        int pathFlow = INT_MAX;

        // encontra o fluxo mínimo ao longo do caminho encontrado pela BFS
        for (int v = V - 1; v != 0; v = parent[v]) {
            int u = parent[v];
            for (Edge& edge : adj[u]) {
                if (edge.to == v) {
                    pathFlow = min(pathFlow, edge.capacity - edge.flow);
                    break;
                }
            }
        }

        // atualiza as capacidades residuais ao longo do caminho
        for (int v = V - 1; v != 0; v = parent[v]) {
            int u = parent[v];
            for (Edge& edge : adj[u]) {
                if (edge.to == v) {
                    edge.flow += pathFlow;
                    break;
                }
            }
            for (Edge& edge : adj[v]) {
                if (edge.to == u) {
                    edge.flow -= pathFlow;
                    break;
                }
            }
        }

        // adiciona o fluxo desse caminho ao fluxo total
        maxFlow += pathFlow;
    }

    return maxFlow;
}

bool Graph::isGenerator (int id) {
    for (int gen : generator_list) if (gen == id) return true;
    return false;
}

void Graph::addGenerator (int id) {
    generator_list.push_back(id);
}

vector<tuple<int, int, int>> Graph::findCriticalConnections() {
    vector<tuple<int, int, int>> critical;

    // adiciona as arestas críticas
    for (int i = 0; i < V; ++i) {
        for (const Edge& edge : adj[i]) {
            if (edge.flow == edge.capacity && edge.capacity > 0 &&
                i != 0 && edge.to != V - 1) {
                critical.emplace_back(i, edge.to, edge.capacity);
            }
        }
    }

    // ordena os cabos pela capacidade, depois origem, depois destino
    for (int i = 0; i < static_cast<int>(critical.size()); ++i) {
        for (int j = i + 1; j < static_cast<int>(critical.size()); ++j) {
            const auto& a = critical[i];
            const auto& b = critical[j];

            // compara capacity
            if (get<2>(a) < get<2>(b)) {
                swap(critical[i], critical[j]);
            } else if (get<2>(a) == get<2>(b)) {
                // compara from
                if (get<0>(a) > get<0>(b)) {
                    swap(critical[i], critical[j]);
                } else if (get<0>(a) == get<0>(b)) {
                    // compara to
                    if (get<1>(a) > get<1>(b)) {
                        swap(critical[i], critical[j]);
                    }
                }
            }
        }
    }

    return critical;
}
