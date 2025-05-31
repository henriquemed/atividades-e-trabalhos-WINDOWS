#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <set>

class Graph {
public:
    // Construtor que inicializa o grafo com um número inicial de nós
    Graph(size_t numNodes);

    // Adiciona uma aresta direcionada do nó 'from' para o nó 'to'
    void addEdge(const std::string& from, const std::string& to);

    // Encontra e retorna a capital do estado
    std::string findCapital();

    // Encontra e retorna os batalhões secundários necessários
    std::vector<std::string> findSecondaryBattalions(const std::string& capitalName);

    // Verifica se o grafo possui um circuito Euleriano
    bool hasEulerianCircuit();

    // Encontra e retorna um circuito Euleriano começando em 'start'
    std::vector<std::string> findEulerianCircuit(const std::string& start);

    // Encontra e retorna um circuito Euleriano no SCC do 'startNodeName'
    std::vector<std::string> getEulerianCircuitInSCC(const std::string& startNodeName);

    // Retorna o número total de arestas no grafo
    size_t getEdgeCount() const;

    // Computa as SCCs do grafo
    void computeSCCs();

private:
    // Mapeia o nome do nó para seu índice
    std::unordered_map<std::string, size_t> nodeMap;

    // Mapeia o índice do nó para seu nome
    std::vector<std::string> indexToName;

    // Lista de adjacência do grafo
    std::vector<std::vector<size_t>> adjList;

    // Lista de adjacência do grafo transposto (reverso)
    std::vector<std::vector<size_t>> reverseAdjList;

    // SCCs do grafo
    std::vector<std::vector<size_t>> SCCs;

    // Mapeia o índice do nó para o índice da SCC
    std::vector<size_t> sccId;

    // Obtém o índice de um nó dado seu nome, adicionando-o se não existir
    size_t getNodeIndex(const std::string& node);

    // Obtém o nome de um nó dado seu índice
    std::string getNodeName(size_t index) const;

    // Preenche a ordem de finalização para o algoritmo de Kosaraju
    void fillOrder(size_t v, std::vector<bool>& visited, std::stack<size_t>& Stack);

    // Realiza DFS a partir de um nó 'v' e coleta os nós na SCC atual
    void DFSUtil(size_t v, std::vector<bool>& visited, const std::vector<std::vector<size_t>>& adj);
    void DFSUtil(size_t v, std::vector<bool>& visited, const std::vector<std::vector<size_t>>& adj, std::vector<size_t>& currentSCC);
};

#endif
