#ifndef ASTAR_H
#define ASTAR_H


#include "../DirectedGraph.h"
#include "../UndirectedGraph.h"
#include <limits>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>


template<typename TV, typename TE>
vector<Vertex<TV,TE>*> reconstruir(unordered_map<TV, TV> padres, Vertex<TV, TE>* actual){
	vector<Vertex<TV,TE>*> camino;
	camino.push_back(actual);

	auto temp = actual;
	while(padres.find(actual) != padres.end()){
		temp = padres[temp];
		camino.push_back(temp); 
	}
	return camino;
}


template<typename TV, typename TE>
auto heuristica = [](Vertex<TV, TE>* inicio, Vertex<TV, TE>* objetivo){
	TE peso;
	int min_peso = INT_MAX;
	Vertex<TV, TE>* min_nodo = nullptr;

	Vertex<TV, TE>* temp = inicio;
	while(temp != objetivo){
		for(auto eje: temp->edges){
			if(eje->weight < min_peso && eje->vertexes[1] != objetivo){
				min_nodo = eje->vertexes[1];
				min_peso = eje->weight;
			} else if(eje->vertexes[1] == objetivo){
				min_nodo = eje->vertexes[1];
				break;
			}
		}
		temp = min_nodo;
		min_peso = INT_MAX;
	}

	return peso;
};


template<typename TV>
auto priorizar_distancia = [](pair<TV,int> edge1, pair<TV,int> edge2){
    return edge1.second > edge2.second;
};


template<typename TV,typename TE>
Vertex<TV,TE>* minDistance(priority_queue<pair<TV,int>,vector<pair<TV,int>>,decltype(priorizar_distancia<TV>)> &distances,DirectedGraph<TV,TE>* grafo){
	Vertex<TV, TE>* temp = grafo->getVertex((distances.top()).first);
	distances.pop();
	return temp;
}


template <typename TV, typename TE>
string astar(UnDirectedGraph<TV,TE>* grafo, string id_partida, string id_llegada){
	priority_queue<pair<TV,int>, vector<pair<TV,int>>, decltype(priorizar_distancia<TV>)> openSet(priorizar_distancia<TV>);
	unordered_map<TV, int> gCosts; // distancia global entre vertices
	unordered_map<TV, int> fCosts; // distancia local entre vertices
	unordered_map<TV, TV> direccion; // padres

	for(int i=0;i<grafo->getNumberVertexes();i++){
		gCosts[grafo->getAllId()[i]] = INT_MAX;
	}
	gCosts[id_partida] = 0;
	

	for(int i=0;i<grafo->getNumberVertexes();i++){
		fCosts[grafo->getAllId()[i]] = INT_MAX;
	}
	fCosts[id_partida] = heuristica(grafo->getVertex(id_partida), grafo->getVertex(id_llegada));
	pair<TV, int> inicial = {id_partida, 0};
	openSet.push(inicial);


	vector<TV> sol;
	while(!openSet.empty()){
		auto current = minDistance(openSet, grafo);
		if(current == grafo->findById(id_llegada)){
			sol = reconstruir(direccion, current);
		}

		openSet.pop();
		for(auto edge: current->edges){
			TE tentative_gCost = gCosts[grafo->find_id(current)] + edge->weight;
			auto vecino = edge->vertexes[1];
			if(tentative_gCost < gCosts[grafo->find_id(vecino)]{
				direccion[grafo->find_id(vecino)] = current;
				gCosts[grafo->find_id(vecino)] = tentative_gCost;
				fCosts[grafo->find_id(vecino)] = tentative_gCost + heuristica(vecino, grafo->findById(id_llegada));

				auto stk = openSet;
				vector<pair<TV, int>> lookKey;
				while(!stk.empty()){
					auto ae = stk.top();
					lookKey.push_back(ae);
					stk.pop();
				}
				if(std::find(lookKey.begin(), lookKey.end(), vecino) == lookKey.end()){
					openSet.push({vecino->data, fCosts[grafo->find_id(vecino)]});
				}
			}
		}
	}
}


#endif