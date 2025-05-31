#include <iostream>
#include <string>

#include "graph.hpp"
#include "capital.hpp"
#include "utils.hpp"
#include "battalions_and_patrols.hpp"

/*
PADRONIZAÇÃO (tentativa)
    nomes em main todos em português

    algoritmos, funções e estruturas mais complexos em inglês

    nome de variavel_eh_assim

    nome de funcaoEhAssim

*/

using namespace std;

int main () {

    // RECEBER A ENTRADA
    
        int n_cidades;
        int n_estradas;
        cin >> n_cidades >> n_estradas;

        vector<string> cidades;

        Graph grafo(n_cidades);

    // CRIAR GRAFO

        for (int i=0, j=0; j < n_estradas; j++) {
            string nome_cidade_A, nome_cidade_B;
            cin >> nome_cidade_A >> nome_cidade_B;
            
            // coloca as cidades na lista se não estiverem
            if (cityAdded(nome_cidade_A, cidades) == -1) {
                cidades.push_back(nome_cidade_A);
                i++;
            }
            if (cityAdded(nome_cidade_B, cidades) == -1) {
                cidades.push_back(nome_cidade_B);
                i++;
            }

            // adiciona aresta entre as cidades
            grafo.addEdge(  cityAdded(nome_cidade_A, cidades), 
                            cityAdded(nome_cidade_B, cidades));

        }

    // CAPITAL: quem é a capital?
        
        vector<int> soma_distancias;

        // roda a bfs pra cada vertice e coloca suas distancias em um vetor
        for (int i = 0; i < n_cidades; i++) {
            vector<int> distancias_vertice_i = bfs(grafo.getMatrix(), i);
            soma_distancias.push_back(sumDistances(distancias_vertice_i));
        }

        // a capital é o elemento no array com a menor soma de distâncias
        int capital_id = minElementId(soma_distancias);
        cout << cidades[capital_id] << endl;

    // BATALHÕES: quantos e quais
        // batalhões são os vértices de componentes conexos mais próximos da capital que não têm
        // um caminho de volta pra ela
        
        // rodar o kosaraju, tendo uma lista de adjacência com as SCCs como resultado
        // lembrete: uma das SCCs é a capital, então basta não imprimi-la
        vector<vector<int>> SCCs = kosaraju(grafo.getMatrix(), capital_id);
        
        // numero de batalhoes
        cout << SCCs.size()-1 << endl;

        // quais sao os batalhoes
        for (size_t i = 0; i < SCCs.size(); i++) {
            if (!(SCCs[i][0] == capital_id)) cout << cidades[SCCs[i][0]] << endl;
        }

    // PATRULHAMENTO: quantas e rotas
        // patrulha é a lista de adjacência do componente conexo

        // quantidade de patrulhas possiveis
        int quant_patrulhas = 0;

        // lista de patrulhas possiveis
        vector<vector<int>> patrulhas;  // vetor que descreve o caminho das patrulhas
        vector<vector<bool>> matriz = grafo.getMatrixbyCopy();

        for (size_t i = 0; i < SCCs.size(); i++) {
            if (!(SCCs[i].size() > 1)) continue;  // se tiver só um node, não tem patrulha aqui
            quant_patrulhas++;

            // construção da rota 

            vector<int> patrulha_atual;
            patrulha_atual.push_back(SCCs[i][0]);   // coloca o batalhão como início

            // navegação na matriz

            int linha_atual = SCCs[i][0];   // inicia no batalhão, na linha dele  
            for (int a = 0; a < n_cidades; a++) {
                if (matriz[linha_atual][a] == 1) {
                    matriz[linha_atual][a] = 0;
                    linha_atual = a;
                    patrulha_atual.push_back(a);    // adiciona essa estrada na rota
                    a = 0;
                }
                // se não houver mais estrada/aresta a seguir, se a chegar ao fim, a patrulha terminou
            }

            // remove o retorno ao batalhão do final da patrulha
            patrulha_atual.pop_back();

            // adiciona a patrulha recém-criada no vetor de patrulhas 
            patrulhas.push_back(patrulha_atual);

            // reseta matriz para computar próxima patrulha
            matriz = grafo.getMatrixbyCopy(); 
        }


        // printar invertido, porque primeiro fazemos tentativas de patrulha e depois contamos
        // quantas são elas
        cout << quant_patrulhas << endl;
        // printa patrulhas
        for (size_t i = 0; i < patrulhas.size(); i++) {
            for (int n : patrulhas[i]) cout << cidades[n] << " ";
            cout << endl;
        }

    return 0;
}
