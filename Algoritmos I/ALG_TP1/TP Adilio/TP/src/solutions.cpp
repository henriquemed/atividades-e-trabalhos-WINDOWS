#include "solutions.hpp"

// Função para encontrar a capital
std::string findCapitalSolution(Graph& graph) {
    return graph.findCapital();
}

// Função para encontrar batalhões secundários
std::vector<std::string> findSecondaryBattalionsSolution(Graph& graph, const std::string& capitalName) {
    return graph.findSecondaryBattalions(capitalName);
}
