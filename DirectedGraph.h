/*
#ifndef NONDIRECTEDGRAPH_H
#define NONDIRECTEDGRAPH_H

#include "graph.h"

template<typename TV, typename TE>
class DirectedGraph : public Graph<TV, TE>{


public:
	DirectedGraph() = default;

	~DirectedGraph(){
		clear();
	};

	bool insertVertex(string id, TV vertex){
		Vertex<TV,TE>* temp = new Vertex<TV,TE>;
		temp->data = vertex;
		temp->edges = list<Edge<TV, TE>*>{};

    if(this->vertexes.find(id) != this->vertexes.end()){
      return false;
    }
    else{
      this->vertexes.emplace(id,temp);
			this->n_vertex++;
      return true;
    }
	}

  bool createEdge(string id1, string id2, TE w){
    if(this->vertexes.find(id1)!= this->vertexes.end() && this->vertexes.find(id2)!= this->vertexes.end()){
      Edge<TV, TE>* arista = new Edge<TV, TE>;
      arista->vertexes[0] = this->vertexes[id1];
      arista->vertexes[1] = this->vertexes[id2];
      arista->weight = w;
      this->n_edges++;
      this->vertexes[id1]->edges.push_back(arista);
      return true;
    }
    else{
      return false;
    }
  }

	bool deleteVertex(string id){
		if(this->vertexes.find(id) == this->vertexes.end()) return false;

		for(auto& vertex: this->vertexes){
			for(auto& edge: vertex.second->edges){
				if(edge->vertexes[0] == this->vertexes[id] || edge->vertexes[1] == this->vertexes[id]){
					vertex.second->edges.remove(edge);
					edge = nullptr;
					delete edge;
					this->n_vertex--;
					break;
				}
			}
		}

		this->vertexes[id]->edges.clear();
		delete this->vertexes[id];
		this->vertexes.erase(id);

		return true;
	}

	bool deleteEdge(string start, string end){
		if(this->vertexes.find(start) == this->vertexes.end() && this->vertexes.find(end) == this->vertexes.end()) return false;

		for(auto& vertex: this->vertexes){
			for(auto& edge: vertex.second->edges){
				if((edge->vertexes[0] == this->vertexes[start] && edge->vertexes[1] == this->vertexes[end]) || (edge->vertexes[1] == this->vertexes[start] && edge->vertexes[0] == this->vertexes[end]) ){
					this->vertexes[start]->edges.remove(edge);
					this->vertexes[end]->edges.remove(edge);
					delete edge;
					this->n_edges--;
					break;
				}
			}
		}
		return true;
	}

	TE &operator()(string start, string end){
		TE val;

		for(auto& vertex: this->vertexes){
			for(auto& edge: vertex.second->edges){
				if(edge->vertexes[0] == this->vertexes[start] && edge->vertexes[1] == this->vertexes[end]){
					val = edge->weight;
				}
			}
		}
		
		return val;
	}

	float density(){
		return this->n_edges/(this->n_vertex*(this->n_vertex-1));
	}

	bool isDense(float threshold = 0.5){
    if(density()>=threshold){
      return true;
    }
    return false;
  }

	bool isConnected(){
		return false;
	}

	bool isStronglyConnected(){
		return false;
	}

	bool empty(){
		if(this->n_edges == 0){
      return true;
    }
    return false;
	}

	void clear(){
		for(auto& vertex1: this->vertexes){
			for(auto& vertex2: this->vertexes){
				if(vertex1.first != vertex2.first) deleteEdge(vertex1.first, vertex2.first);
			}
		}

		for(auto& vertex: this->vertexes){
			deleteVertex(vertex.first);
		}
	}
		
	void displayVertex(string id){
		if(this->vertexes.find(id) == this->vertexes.end()) throw("No existe vertice");
		
		std::cout << this->vertexes[id]->data << std::endl;
	}

	bool findById(string id){
    return this->vertexes.find(id) == this->vertexes.end();
  }

	void display(){
    cout << "------Matriz de adyasencia------" << endl;
    for(auto &vertex : this->vertexes){
      cout<<vertex.first<<" | ";
      for(auto &edge : vertex.second->edges){
        cout<<edge->vertexes[1]->data<<" ";
      }
      cout<<endl;
    }
    cout << "--------------------------------" << endl;
	}
};

#endif
*/