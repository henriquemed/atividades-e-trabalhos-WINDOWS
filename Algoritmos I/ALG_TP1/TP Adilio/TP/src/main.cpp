#include <iostream>
#include "graph.hpp"
#include "solutions.hpp"

int main() {
    size_t numNodesInput, numEdges;
    std::cin >> numNodesInput >> numEdges;

    Graph graph(numNodesInput);

    for (size_t i = 0; i < numEdges; ++i) {
        std::string from, to;
        std::cin >> from >> to;
        graph.addEdge(from, to);
    }

    // Parte I: Encontrar a capital
    std::string capital = findCapitalSolution(graph);
    std::cout << capital << std::endl;

    // Parte II: Encontrar batalhões secundários
    std::vector<std::string> battalions = findSecondaryBattalionsSolution(graph, capital);
    std::cout << battalions.size() << std::endl;
    for (const auto& battalion : battalions) {
        std::cout << battalion << std::endl;
    }

    // Parte III: Patrulhamento
    // Include capital in list of battalions for patrol routes
    std::vector<std::string> patrolStartPoints = battalions;
    patrolStartPoints.insert(patrolStartPoints.begin(), capital);

    std::vector<std::vector<std::string>> patrolRoutes;

    for (const auto& startPoint : patrolStartPoints) {
        std::vector<std::string> route = graph.getEulerianCircuitInSCC(startPoint);
        // Ignore circuits with only 1 city, because there's no patrol possible
        if (route.size() > 1) {
            patrolRoutes.push_back(route);
        }
    }

    // Output the number of patrol routes
    std::cout << patrolRoutes.size() << std::endl;

    // Remove the returning route and output the patrol routes
    for (auto& route : patrolRoutes) {
        route.pop_back();
        for (const auto& node : route) {
            std::cout << node << " ";
        }
        std::cout << std::endl;
    }


    return 0;
}
