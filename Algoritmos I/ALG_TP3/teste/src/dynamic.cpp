#include "dynamic.hpp"

int tsp(int mask, int pos, vector<vector<int>> &dist, vector<vector<int>> &sub_results, int n) {
    //caso base: se todas as cidades já foram visitadas, retorna à origem
    if (mask == (1 << n) - 1) {
        return dist[pos][0];
    }

    // se já foi calculado para esse estado retorna o valor memorizado
    if (sub_results[mask][pos] != -1) {
        return sub_results[mask][pos];
    }

    int smallest_cost = INF; // inicializa com um valor muito alto (infinito)
    
    // percorre todas as cidades para tentar visitar a próxima
    for (int city = 0; city < n; city++) {
        // se a cidade ainda não foi visitada e há uma estrada entre as cidades
        if ((mask & (1 << city)) == 0 && dist[pos][city] != 0) {
            // chama recursivamente a função para a próxima cidade
            int new_smallest_cost = dist[pos][city] + tsp(mask | (1 << city), city, dist, sub_results, n);
            smallest_cost = min(smallest_cost, new_smallest_cost); // mantém o custo mínimo
        }
    }

    return sub_results[mask][pos] = smallest_cost;
}

vector<int> solveTSPDynamic(Graph &g) {
    int n = g.n_vertices;    

    vector<vector<int>> dist(n, vector<int>(n, 0)); // matriz de distâncias entre as cidades

    // tabela para armazenar os resultados dos subproblemas
    vector<vector<int>> sub_results(1 << n, vector<int>(n, -1));

    // inicializa a matriz de distâncias a partir do gráfico
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            dist[i][j] = g.hasRoad(i, j);
            if (dist[i][j] == 0) {
                dist[i][j] = INF;
            }
        }
    }

    // chama a função recursiva tsp começando pela cidade 0 e com o estado inicial
    int minCost = tsp(1, 0, dist, sub_results, n);

    vector<int> path;
    int mask = 1;  // representa a cidade 0 como já visitada
    int pos = 0;   // começa na cidade 0

    // reconstrói o caminho percorrido
    while (mask != (1 << n) - 1) {
        path.push_back(pos); // adiciona a cidade atual ao caminho
        
        int nextCity = -1;
        int minDist = INF; // inicializa com um valor simbólico muito alto

        // tenta encontrar a próxima cidade com o menor custo
        for (int city = 0; city < n; ++city) {
            if (!(mask & (1 << city)) && dist[pos][city] != INF) {
                // verifica se o custo de ir para a cidade 'city' é menor que o atual
                if (sub_results[mask | (1 << city)][city] + dist[pos][city] < minDist) {
                    minDist = sub_results[mask | (1 << city)][city] + dist[pos][city];
                    nextCity = city;
                }
            }
        }

        if (nextCity == -1) break; // caso não haja cidade próxima válida, dá um break

        pos = nextCity;
        mask |= (1 << pos);
    }

    path.push_back(pos);     // adiciona a última cidade antes de retornar ao inicio
    path.push_back(0);       // retorna à cidade inicial
    path.push_back(minCost); // adiciona o custo mínimo total ao final do caminho

    return path;
}