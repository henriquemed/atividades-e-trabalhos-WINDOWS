#include "battalions_and_patrols.hpp"
#include <vector>
#include <stack>

using namespace std;

void dfsOrder(const vector<vector<bool>>& adj, int node, vector<bool>& visited, stack<int>& order) {
    visited[node] = true;
    for (int neighbor = 0; neighbor < static_cast<int>(adj.size()); ++neighbor) {
        if (adj[node][neighbor] && !visited[neighbor]) {
            dfsOrder(adj, neighbor, visited, order);
        }
    }
    order.push(node);
}

void dfsSCC(const vector<vector<bool>>& adj, int node, vector<bool>& visited, vector<int>& scc) {
    visited[node] = true;
    scc.push_back(node);
    for (int neighbor = 0; neighbor < static_cast<int>(adj.size()); ++neighbor) {
        if (adj[node][neighbor] && !visited[neighbor]) {
            dfsSCC(adj, neighbor, visited, scc);
        }
    }
}

vector<vector<bool>> transposeGraph(const vector<vector<bool>>& adj) {
    int n = static_cast<int>(adj.size());
    vector<vector<bool>> transposed(n, vector<bool>(n, false));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            transposed[j][i] = adj[i][j];
        }
    }
    return transposed;
}

vector<vector<int>> kosaraju(const vector<vector<bool>>& adj, int startNode) {
    int n = static_cast<int>(adj.size());
    vector<bool> visited(n, false);
    stack<int> order;

    // PASSO 1: INICIAR DFS DA CAPITAL
    dfsOrder(adj, startNode, visited, order);

    // GARANTE QUE OUTROS NOS SEJAM PROCESSADOS MESMO DESCONEXOS
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfsOrder(adj, i, visited, order);
        }
    }

    // PASSO 2: TRANSPOR O GRAFO
    vector<vector<bool>> transposed = transposeGraph(adj);

    // PASSO 3: ENCCONTRAR SCCS
    for (int i = 0; i < n; ++i) {
        visited[i] = false;
    }

    vector<vector<int>> sccs;

    while (!order.empty()) {
        int node = order.top();
        order.pop();

        if (!visited[node]) {
            vector<int> scc;
            dfsSCC(transposed, node, visited, scc);
            sccs.push_back(scc);
        }
    }

    return sccs;
}
