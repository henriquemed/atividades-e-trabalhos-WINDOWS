#include "graph.hpp"

Graph::Graph(int n_nodes) {
    n_nodes_ = n_nodes;
    matrix_ = vector<vector<bool>> (n_nodes, vector<bool>(n_nodes, false));
}

Graph::~Graph() {}


bool Graph::rangeIsValid (int node_id) {
    if (node_id >= 0 && node_id < n_nodes_) return true;
    else {
        cout << "Erro: No fora do intervalo!" << endl;
        return false;
    }
}

void Graph::addEdge(int from_node, int to_node) {
    if (rangeIsValid(from_node) && rangeIsValid(to_node)) matrix_[from_node][to_node] = true;
}

bool Graph::hasEdge(int from_node, int to_node) {
    if (rangeIsValid(from_node) && rangeIsValid(to_node)) return matrix_[from_node][to_node];
    else {
        exit(1);
        return 0;
    }
}

vector<vector<bool>>& Graph::getMatrix () {
    return matrix_;
}

vector<vector<bool>> Graph::getMatrixbyCopy () {
    return matrix_;
}


void Graph::print_graph() {
    for (int i = 0; i < n_nodes_; ++i) {
        for (int j = 0; j < n_nodes_; ++j) {
            cout << (matrix_[i][j] ? 1 : 0) << " ";
        }
        cout << endl;
    }
}
