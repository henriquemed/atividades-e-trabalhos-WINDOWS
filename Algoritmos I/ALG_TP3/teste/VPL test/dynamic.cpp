#include "dynamic.hpp"

void dfs(int current, vector<int> path, int cost, vector<vector<int>>& tree, Graph& g, vector<bool>& visited, int root) {
    path.push_back(current);
    
    if (current != root) cost += g.hasRoad(path[path.size() - 2], current);
    
    if ((int)path.size() == g.n_vertices) {
        if (g.hasRoad(current, root) > 0) {
            path.push_back(root);
            cost += g.hasRoad(current, root);
            path.push_back(cost);
            tree.push_back(path);
        }
        return;
    }
    
    visited[current] = true;
    for (int i = 0; i < g.n_vertices; i++) {
        if (!visited[i] && g.hasRoad(current, i) > 0) {
            dfs(i, path, cost, tree, g, visited, root);
        }
    }
    visited[current] = false;
}

vector<vector<int>> buildTree(int root, Graph g) {
    vector<vector<int>> tree;
    vector<bool> visited(g.n_vertices, false);
    dfs(root, {}, 0, tree, g, visited, root);
    return tree;
}

vector<vector<vector<int>>> buildPossibilityTrees(int n_cities, Graph g) {
    vector<vector<vector<int>>> tree_vector(n_cities);
    for (int i = 0; i < n_cities; i++) {
        tree_vector[i] = buildTree(i, g);
    }
    return tree_vector;
}

vector<int> returnSmallestPath(vector<vector<vector<int>>> tree_vector) {
    vector<int> smallest_path;
    int smallest_cost = 99999;
    
    for (const auto& tree : tree_vector) {
        for (const auto& path : tree) {
            int cost = path.back(); // último elemento é o custo
            if (cost < smallest_cost) {
                smallest_cost = cost;
                smallest_path = path;
            }
        }
    }
    
    return smallest_path;
}
