#ifndef SOLUTIONS_HPP
#define SOLUTIONS_HPP

#include "graph.hpp"
#include <string>
#include <vector>

// Declarações das funções
std::string findCapitalSolution(Graph& graph);
std::vector<std::string> findSecondaryBattalionsSolution(Graph& graph, const std::string& capitalName);

#endif
