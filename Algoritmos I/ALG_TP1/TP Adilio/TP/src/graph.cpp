#include "graph.hpp"
#include <queue>
#include <limits>
#include <set>
#include <stack>

using namespace std;

// Construtor do Grafo
Graph::Graph(size_t numNodes) : 
      nodeMap(),
      indexToName(),
      adjList(numNodes),
      reverseAdjList(numNodes),
      SCCs(),
      sccId() {}

// Obter ou atribuir índice para um nó
size_t Graph::getNodeIndex(const string& node) {
    auto it = nodeMap.find(node);
    if (it == nodeMap.end()) {
        size_t index = nodeMap.size();
        nodeMap[node] = index;
        if (index >= adjList.size()) {
            adjList.resize(index + 1);
            reverseAdjList.resize(index + 1);
        }
        indexToName.push_back(node);
        return index;
    }
    return it->second;
}

// Obter nome do nó a partir do índice
string Graph::getNodeName(size_t index) const {
    if (index < indexToName.size()) {
        return indexToName[index];
    }
    return "";
}

// Adicionar uma aresta ao grafo
void Graph::addEdge(const string& from, const string& to) {
    size_t fromIndex = getNodeIndex(from);
    size_t toIndex = getNodeIndex(to);

    adjList[fromIndex].push_back(toIndex);
    reverseAdjList[toIndex].push_back(fromIndex);
}

// Encontrar a capital
string Graph::findCapital() {
    size_t capitalIndex = SIZE_MAX;
    int minEccentricity = numeric_limits<int>::max();

    for (size_t i = 0; i < adjList.size(); ++i) {
        vector<int> distances(adjList.size(), -1);
        queue<size_t> q;
        q.push(i);
        distances[i] = 0;

        while (!q.empty()) {
            size_t u = q.front();
            q.pop();
            for (size_t v : adjList[u]) {
                if (distances[v] == -1) {
                    distances[v] = distances[u] + 1;
                    q.push(v);
                }
            }
        }

        bool allReachable = true;
        int currentMax = 0;
        for (int dist : distances) {
            if (dist == -1) {
                allReachable = false;
                break;
            }
            if (dist > currentMax) currentMax = dist;
        }

        if (allReachable && currentMax < minEccentricity) {
            minEccentricity = currentMax;
            capitalIndex = i;
        }
    }

    return getNodeName(capitalIndex);
}

// Função auxiliar para preencher a ordem de finalização
void Graph::fillOrder(size_t v, vector<bool>& visited, stack<size_t>& Stack) {
    visited[v] = true;
    for (size_t adjNode : adjList[v]) {
        if (!visited[adjNode]) {
            fillOrder(adjNode, visited, Stack);
        }
    }
    Stack.push(v);
}

// Função auxiliar para realizar DFS e coletar os nós da SCC
void Graph::DFSUtil(size_t v, vector<bool>& visited, const vector<vector<size_t>>& adj, vector<size_t>& currentSCC) {
    visited[v] = true;
    currentSCC.push_back(v);
    for (size_t adjNode : adj[v]) {
        if (!visited[adjNode]) {
            DFSUtil(adjNode, visited, adj, currentSCC);
        }
    }
}

// Overloaded DFSUtil para checar conectividade
void Graph::DFSUtil(size_t v, vector<bool>& visited, const vector<vector<size_t>>& adj) {
    visited[v] = true;
    for (size_t adjNode : adj[v]) {
        if (!visited[adjNode]) {
            DFSUtil(adjNode, visited, adj);
        }
    }
}

// Computa as SCCs do grafo
void Graph::computeSCCs() {
    stack<size_t> Stack;
    vector<bool> visited(adjList.size(), false);

    for (size_t i = 0; i < adjList.size(); ++i) {
        if (!visited[i]) {
            fillOrder(i, visited, Stack);
        }
    }

    vector<vector<size_t>> transpose = reverseAdjList;

    fill(visited.begin(), visited.end(), false);

    SCCs.clear();
    sccId.assign(adjList.size(), SIZE_MAX);

    while (!Stack.empty()) {
        size_t v = Stack.top();
        Stack.pop();

        if (!visited[v]) {
            vector<size_t> currentSCC;
            DFSUtil(v, visited, transpose, currentSCC);

            size_t currentSccIndex = SCCs.size();
            for (size_t node : currentSCC) {
                sccId[node] = currentSccIndex;
            }

            SCCs.push_back(currentSCC);
        }
    }
}

// Encontrar batalhões secundários
vector<string> Graph::findSecondaryBattalions(const string& capitalName) {
    computeSCCs();

    size_t numSCCs = SCCs.size();
    vector<set<size_t>> condAdjList(numSCCs);
    for (size_t u = 0; u < adjList.size(); ++u) {
        size_t sccU = sccId[u];
        for (size_t v : adjList[u]) {
            size_t sccV = sccId[v];
            if (sccU != sccV) {
                condAdjList[sccU].insert(sccV);
            }
        }
    }

    vector<set<size_t>> reverseCondAdjList(numSCCs);
    for (size_t u = 0; u < condAdjList.size(); ++u) {
        for (size_t v : condAdjList[u]) {
            reverseCondAdjList[v].insert(u);
        }
    }

    size_t capitalIndex = getNodeIndex(capitalName);
    size_t capitalSCC = sccId[capitalIndex];

    vector<bool> visitedSCC(numSCCs, false);
    queue<size_t> q;
    q.push(capitalSCC);
    visitedSCC[capitalSCC] = true;

    while (!q.empty()) {
        size_t scc = q.front();
        q.pop();
        for (size_t adjSCC : reverseCondAdjList[scc]) {
            if (!visitedSCC[adjSCC]) {
                visitedSCC[adjSCC] = true;
                q.push(adjSCC);
            }
        }
    }

    vector<string> battalions;
    for (size_t i = 0; i < numSCCs; ++i) {
        if (!visitedSCC[i]) {
            battalions.push_back(getNodeName(SCCs[i][0]));
        }
    }

    return battalions;
}

std::vector<std::string> Graph::getEulerianCircuitInSCC(const std::string& startNodeName) {
    // Certifique-se de que as SCCs estão computadas
    if (sccId.empty()) {
        computeSCCs();
    }

    // Obter o índice do nó inicial e a SCC correspondente
    size_t startNodeIndex = getNodeIndex(startNodeName);
    size_t sccIndex = sccId[startNodeIndex];
    const std::vector<size_t>& sccNodes = SCCs[sccIndex];

    // Mapear os nós da SCC para um índice local
    std::unordered_map<size_t, size_t> nodeIndexMap;
    for (size_t i = 0; i < sccNodes.size(); ++i) {
        nodeIndexMap[sccNodes[i]] = i;
    }

    // Construir lista de adjacência da SCC
    std::vector<std::vector<size_t>> sccAdjList(sccNodes.size());
    for (size_t u : sccNodes) {
        size_t uLocal = nodeIndexMap[u];
        for (size_t v : adjList[u]) {
            if (nodeIndexMap.find(v) != nodeIndexMap.end()) {
                size_t vLocal = nodeIndexMap[v];
                sccAdjList[uLocal].push_back(vLocal);
            }
        }
    }

    // Validar condições de circuito Euleriano na SCC
    std::vector<size_t> inDegree(sccNodes.size(), 0);
    std::vector<size_t> outDegree(sccNodes.size(), 0);
    for (size_t u = 0; u < sccNodes.size(); ++u) {
        outDegree[u] = sccAdjList[u].size();
        for (size_t v : sccAdjList[u]) {
            inDegree[v]++;
        }
    }

    for (size_t i = 0; i < sccNodes.size(); ++i) {
        if (inDegree[i] != outDegree[i]) {
            return {}; // Não é possível formar um circuito Euleriano
        }
    }

    // Encontrar o circuito Euleriano usando o algoritmo de Hierholzer
    std::vector<std::string> circuit;
    std::stack<size_t> currPath;
    std::vector<std::vector<size_t>> tempAdjList = sccAdjList;

    size_t startLocal = nodeIndexMap[startNodeIndex];
    currPath.push(startLocal);

    while (!currPath.empty()) {
        size_t current = currPath.top();
        if (!tempAdjList[current].empty()) {
            size_t next = tempAdjList[current].back();
            tempAdjList[current].pop_back();
            currPath.push(next);
        } else {
            circuit.push_back(getNodeName(sccNodes[current]));
            currPath.pop();
        }
    }

    // Reversão manual do circuito
    std::vector<std::string> reversedCircuit;
    for (int i = circuit.size() - 1; i >= 0; --i) {
        reversedCircuit.push_back(circuit[i]);
    }

    return reversedCircuit;
}
