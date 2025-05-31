#include <iostream>
#include "graph.hpp"

using namespace std;

int main() {

    // resolvi padronizar o código todo em inglês
    // no último TP fiz misturado e não ficou legal

// ENTRADAS

    // para facilitar meu raciocínio, 
    // decidi chamar as conexões de cabos
    // e os geradores e consumidores de pontos 
    // (pontos de fornecimento e consumo)
    int n_points, n_cables;
    cin >> n_points >> n_cables;

    // instancia o grafo com duas arestas adicionais, 
    // source (índice = 0) e sink (índice = n_points + 1)
    Graph g(n_points + 2); 

    // demanda total. usaremos isso mais tarde
    int total_demand = 0;

    // ENTRADA DOS PONTOS

        for (int i = 0; i < n_points; ++i) {
            int id, demand;
            cin >> id >> demand;

            if (id < 1 || id > n_points) {
                cerr << "Error: ID is out of range." << endl;
                cout << id << " " << demand << endl;
                exit(1);
            }

            // acrescenta à demanda total
            total_demand += demand;

            if (demand == 0) { // é um gerador
                g.addEdge(0, id, INT_MAX); // conecta à source
                g.addGenerator(id);
            } else { // é um consumidor
                g.setDemand(id, demand);
                g.addEdge(id, n_points + 1, demand); // conecta à sink
            }
        }

    // ENTRADA DOS CABOS, OU SEJA, CONEXÕES

        // demanda total dos cabos. usaremos isso mais tarde
        int total_cable_capacity = 0;

        // energia total que sai dos geradores por cabos conectados a eles
        int generated_energy = 0;

        for (int i = 0; i < n_cables; ++i) {
            int from, to, capacity;
            cin >> from >> to >> capacity;

            if (from < 1 || from > n_points || to < 1 || to > n_points) {
                cerr << "Error: ID connection out of range." << endl;
                cout << from << " " << to << " " << capacity << endl;
                exit(1);
            }

            // acrescenta à demanda total
            total_cable_capacity += capacity;

            // se sai de um gerador, soma à energia gerada
            if (g.isGenerator(from)) generated_energy += capacity;

            g.addEdge(from, to, capacity);
        }


// SAÍDAS

    // E_total
    int maxEnergy = g.calculateMaxFlow();
    cout << maxEnergy << endl;

    // E_missing
    int unmetDemand = total_demand - maxEnergy;
    cout << unmetDemand << endl;

    // E_loss
    int lostEnergy = generated_energy - maxEnergy;
    cout << lostEnergy << endl;

    // P_critical
    vector<tuple<int, int, int>> critical = g.findCriticalConnections();
    cout << critical.size() << endl;
    for (const auto& connection : critical) {
        cout << get<0>(connection) << " " << get<1>(connection) << " " << get<2>(connection) << endl;
    }

    return 0;
}
