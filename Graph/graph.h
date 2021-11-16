#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

template<typename TV, typename TE>
struct Edge;

template<typename TV, typename TE>
struct Vertex;

template<typename TV, typename TE>
class Graph;

//////////////////////////////////////////////////////

template<typename TV, typename TE>
struct Edge {
	Vertex<TV, TE>* vertexes[2];
	TE weight;

    bool operator>(Edge other) {
        if (this->weight > other.edge) { return true; } else { false; }
    }
};

template<typename TV, typename TE>
struct Vertex {
	TV data;
	std::list<Edge<TV, TE>*> edges;
};

template<typename TV, typename TE>
class Graph{
protected:
	int n_edges=0;
	int n_vertex=0;  
	std::unordered_map<string, Vertex<TV, TE>*>  vertexes;
    
public:
    virtual ~Graph() {};
    virtual bool insertVertex(string id, TV vertex) = 0;
    virtual bool createEdge(string id1, string id2, TE w) = 0;
    virtual bool deleteVertex(string id) = 0;
    virtual bool deleteEdge(string start, string end) = 0;
    virtual TE &operator()(string start, string end)= 0;
    virtual float density() = 0;
    virtual bool isDense(float threshold = 0.5) = 0;
    virtual bool isConnected()= 0;
    virtual bool isStronglyConnected() = 0;
    virtual bool empty() = 0;
    virtual void clear()= 0;

    virtual void displayVertex(string id)= 0;
    virtual bool findById(string id) = 0;
    virtual void display() = 0;

	Vertex<TV, TE>* getVertex(string id){
		return this->vertexes[id];
	}

    std::vector<Edge<TV, TE>*, bool> getAllEdges(){
        std::vector<Edge<TV, TE>*, bool> edges;
        for (auto &vertex : this->vertexes) {
            for (auto &edge : vertex.second->edges) {
                edges.push_back(edge) = false;
            }
        }
        return edges;
    }
};

#endif