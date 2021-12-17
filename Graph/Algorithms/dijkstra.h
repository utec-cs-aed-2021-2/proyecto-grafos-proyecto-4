#ifndef dijkstra_H
#define dijkstra_H

#include "../DirectedGraph.h"
#include "../UndirectedGraph.h"
#include <limits>
#include<map>
#include <queue>

template<typename TV>
auto priorizar_distancia = [](pair<TV,int> edge1,pair<TV,int> edge2){
    return edge1.second > edge2.second;
};

template<typename TV>
bool anyFalse(unordered_map<TV,bool> visited){
    for(auto it=visited.begin();it!=visited.end();it++){
        if((*it).second == false){
            return true;
        }
    }
    return false;
}

template<typename TV,typename TE>
Vertex<TV,TE>* minDistance(priority_queue<pair<TV,int>,vector<pair<TV,int>>,decltype(priorizar_distancia<TV>)> &distances,DirectedGraph<TV,TE>* grafo){
    Vertex<TV, TE>* temp = grafo->getVertex((distances.top()).first);
    distances.pop();
    return temp;
}


template <typename TV, typename TE>
string dijkstra(DirectedGraph<TV,TE>* grafo, string id_partida, string id_llegada){
    int IFN=100000;
    priority_queue<pair<TV,int>,vector<pair<TV,int>>,decltype(priorizar_distancia<TV>)> distances(priorizar_distancia<TV>);
    unordered_map<TV,bool> visited; //vertices ya visitados
    unordered_map<TV,int> distance; //distancias entre vertices
    unordered_map<TV,TV> parents; // padres
    

    //algoritmo
    
    for(int i=0;i<grafo->getNumberVertexes();i++){
        visited[grafo->getAllId()[i]]=false;
        distance[grafo->getAllId()[i]]=IFN;
    }

    distance[id_partida]=0;
    pair<TV,int> temp_pair={id_partida,0};
    distances.push(temp_pair);

    while(!distances.empty()){
        Vertex<TV,TE>* minima = minDistance(distances,grafo);
        visited[grafo->find_id(minima)] = true;

        auto temp_edges = grafo->getEdges(minima);
        for(auto it=temp_edges.begin();it!=temp_edges.end();it++){
            if(!visited[grafo->find_id((*it)->vertexes[1])]){
                if(distance[grafo->find_id((*it)->vertexes[1])] > distance[grafo->find_id((*it)->vertexes[0])] + (*it)->weight){
                    distance[grafo->find_id((*it)->vertexes[1])] = distance[grafo->find_id((*it)->vertexes[0])] + (*it)->weight;
                    parents[grafo->find_id((*it)->vertexes[1])] = grafo->find_id((*it)->vertexes[0]);
                    temp_pair = {grafo->find_id((*it)->vertexes[1]),(*it)->weight};
                    distances.push(temp_pair);
                }
            }
        }
    }

    //retrono del resultado en un string
    string temp_text = id_llegada;
    string solution="";

    solution +=id_llegada;
    solution +=" ";
    while(temp_text != id_partida){
        solution +=parents[temp_text];
        solution +=" ";
        temp_text = parents[temp_text];
    }
    return solution;
}

template<typename TV,typename TE>
Vertex<TV,TE>* minDistance(priority_queue<pair<TV,int>,vector<pair<TV,int>>,decltype(priorizar_distancia<TV>)> &distances,UnDirectedGraph<TV,TE>* grafo){
    Vertex<TV, TE>* temp = grafo->getVertex((distances.top()).first);
    distances.pop();
    return temp;
}

template <typename TV, typename TE>
string dijkstra(UnDirectedGraph<TV,TE>* grafo, string id_partida, string id_llegada){
    int IFN=100000;
    priority_queue<pair<TV,int>,vector<pair<TV,int>>,decltype(priorizar_distancia<TV>)> distances(priorizar_distancia<TV>);
    unordered_map<TV,bool> visited; //vertices ya visitados
    unordered_map<TV,int> distance; //distancias entre vertices
    unordered_map<TV,TV> parents; // padres
    

    //algoritmo
    
    for(int i=0;i<grafo->getNumberVertexes();i++){
        visited[grafo->getAllId()[i]]=false;
        distance[grafo->getAllId()[i]]=IFN;
    }

    distance[id_partida]=0;
    pair<TV,int> temp_pair={id_partida,0};
    distances.push(temp_pair);

    while(!distances.empty()){
        Vertex<TV,TE>* minima = minDistance(distances,grafo);
        visited[grafo->find_id(minima)] = true;

        auto temp_edges = grafo->getEdges(minima);
        for(auto it=temp_edges.begin();it!=temp_edges.end();it++){
            if(!visited[grafo->find_id((*it)->vertexes[1])]){
                if(distance[grafo->find_id((*it)->vertexes[1])] > distance[grafo->find_id((*it)->vertexes[0])] + (*it)->weight){
                    distance[grafo->find_id((*it)->vertexes[1])] = distance[grafo->find_id((*it)->vertexes[0])] + (*it)->weight;
                    parents[grafo->find_id((*it)->vertexes[1])] = grafo->find_id((*it)->vertexes[0]);
                    temp_pair = {grafo->find_id((*it)->vertexes[1]),(*it)->weight};
                    distances.push(temp_pair);
                }
            }
        }
    }

    //retrono del resultado en un string
    string temp_text = id_llegada;
    string solution="";

    solution +=id_llegada;
    solution +=" ";
    while(temp_text != id_partida){
        solution +=parents[temp_text];
        solution +=" ";
        temp_text = parents[temp_text];
    }
    return solution;
}

#endif