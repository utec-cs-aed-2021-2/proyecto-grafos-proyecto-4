#ifndef DFS_H
#define DFS_H

#include "../DirectedGraph.h"
#include "../UndirectedGraph.h"
#include <stack>


template <typename TV, typename TE>
vector<Vertex<TV,TE>*> dfs(DirectedGraph<TV,TE>* grafo, string id_partida){
	if(!grafo->findById(id_partida)) throw("Alguno de los nodos no existe");


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
	
	stack<Vertex<TV, TE>*> stk;
	vector<Vertex<TV, TE>*> visited;
	vector<Vertex<TV, TE>*> sol;

	stk.push(grafo->getVertex(id_partida));
	
	while(!stk.empty()){
		auto temp = stk.top();
		stk.pop();

		if(!buscar_elemento(visited, temp)){
			sol.push_back(temp);
			visited.push_back(temp);
		}

		for(auto &edge: temp->edges){
            if(edge->vertexes[0] == temp) {
                if(!buscar_elemento(visited, edge->vertexes[1])){
                    stk.push(edge->vertexes[1]);
                }
            }
		}
	}

	return sol; 
}

template <typename TV, typename TE>
vector<Vertex<TV,TE>*> dfs(Graph<TV,TE>* grafo, string id_partida){
    if(!grafo->findById(id_partida)) throw("Alguno de los nodos no existe");


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

    stack<Vertex<TV, TE>*> stk;
    vector<Vertex<TV, TE>*> visited;
    vector<Vertex<TV, TE>*> sol;

    stk.push(grafo->getVertex(id_partida));

    while(!stk.empty()){
        auto temp = stk.top();
        stk.pop();

        if(!buscar_elemento(visited, temp)){
            sol.push_back(temp);
            visited.push_back(temp);
        }

        for(auto &edge: temp->edges){
            if(edge->vertexes[0] == temp) {
                if(!buscar_elemento(visited, edge->vertexes[1])){
                    stk.push(edge->vertexes[1]);
                }
            }
            else {
                if(!buscar_elemento(visited, edge->vertexes[0])){
                    stk.push(edge->vertexes[0]);
                }
            }
        }
    }

    return sol;
}



#endif