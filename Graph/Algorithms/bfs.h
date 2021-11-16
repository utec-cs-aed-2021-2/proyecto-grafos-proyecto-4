#ifndef BFS_H
#define BFS_H

#include "../DirectedGraph.h"
#include "../UndirectedGraph.h"
#include <utility>
#include <queue>
#include <stack>
#include <unordered_map>

template <typename TV, typename TE>
vector<Vertex<TV,TE>*> bfs(DirectedGraph<TV,TE>* grafo, string id_partida){
	if(!grafo->findById(id_partida)) throw("No existe el nodo inicial");

	auto buscar_elemento = [](vector<Vertex<TV, TE>*> vect, Vertex<TV, TE>* vertex){
		bool is_visited = false;
		for(auto it=vect.begin(); it!=vect.end(); ++it){
			if(*it == vertex){
				is_visited = true;
				break;
			}
		}
		return is_visited;
	};


    queue<Vertex<TV, TE>*> cola;
	vector<Vertex<TV, TE>*> visitados;
    vector<Vertex<TV, TE>*> sol;

	Vertex<TV, TE>* inicio = grafo->getVertex(id_partida);
  cola.push(inicio);

	while(!cola.empty()){
		auto temp = cola.front();
		cola.pop();

    sol.push_back(temp);
    visitados.push_back(temp);

		for(auto &edge: temp->edges){
            if (edge->vertexes[0] == temp) {
                if (!buscar_elemento(visitados, edge->vertexes[1])) {
                    visitados.push_back(edge->vertexes[1]);
                    cola.push(edge->vertexes[1]);
                }
            }
		}
	}

	return sol;
}

template <typename TV, typename TE>
vector<Vertex<TV,TE>*> bfs(UnDirectedGraph<TV,TE>* grafo, string id_partida){
    if(!grafo->findById(id_partida)) throw("No existe el nodo inicial");

    auto buscar_elemento = [](vector<Vertex<TV, TE>*> vect, Vertex<TV, TE>* vertex){
        bool is_visited = false;
        for(auto it=vect.begin(); it!=vect.end(); ++it){
            if(*it == vertex){
                is_visited = true;
                break;
            }
        }
        return is_visited;
    };


    queue<Vertex<TV, TE>*> cola;
    vector<Vertex<TV, TE>*> visitados;
    vector<Vertex<TV, TE>*> sol;

    Vertex<TV, TE>* inicio = grafo->getVertex(id_partida);
    cola.push(inicio);

    while(!cola.empty()){
        auto temp = cola.front();
        cola.pop();

        sol.push_back(temp);
        visitados.push_back(temp);

        for(auto &edge: temp->edges){
            if (edge->vertexes[0] == temp){
                if(!buscar_elemento(visitados, edge->vertexes[1])){
                    visitados.push_back(edge->vertexes[1]);
                    cola.push(edge->vertexes[1]);
                }
            }
            else {
                if(!buscar_elemento(visitados, edge->vertexes[0])){
                    visitados.push_back(edge->vertexes[0]);
                    cola.push(edge->vertexes[0]);
                }
            }
        }
    }

    return sol;
}

#endif