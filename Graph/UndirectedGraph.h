#ifndef UNDIRECTEDGRAPH_H
#define UNDIRECTEDGRAPH_H

#include "graph.h"

template<typename TV, typename TE>
class UnDirectedGraph : public Graph<TV, TE>{

public:
    UnDirectedGraph() = default;

    ~UnDirectedGraph(){
        clear();
    };

    bool insertVertex(string id, TV vertex){
        // COMPLETED
        // Duplicate Case: Returns False
        if(this->vertexes.find(id) != this->vertexes.end()){
            return false;
        }
        // Standard Case: Insertion
        auto temp = new Vertex<TV,TE>;
        temp->data = vertex;
        temp->edges = list<Edge<TV, TE>*>{};
        this->vertexes.emplace(id,temp);
        this->n_vertex++;
        return true;
    }

    bool createEdge(string id1, string id2, TE w){
        // COMPLETED
        // Vertex do not exist Case: Returns False
        if(this->vertexes.find(id1) == this->vertexes.end()) {
            return false;
        }
        if(this->vertexes.find(id2) == this->vertexes.end()) {
            return false;
        }
        // Standard Case: Insertion
        auto arista = new Edge<TV, TE>;
        arista->vertexes[0] = this->vertexes[id1]; // vertex0
        arista->vertexes[1] = this->vertexes[id2]; // vertex1
        arista->weight = w;
        this->n_edges++;
        this->vertexes[id1]->edges.push_back(arista);
        this->vertexes[id2]->edges.push_back(arista);
        return true;
    }

    bool deleteVertex(string id){
        // COMPLETED
        // Vertex does not exist Case: Returns False
        if(this->vertexes.find(id) == this->vertexes.end()) return false;
        // Standard Case: Deletion
        while (!this->vertexes[id]->edges.empty()){
            auto arista = this->vertexes[id]->edges.front();
            auto other = (arista->vertexes[0] == this->vertexes[id] ) ? arista->vertexes[1] : arista->vertexes[0];
            other->edges.remove(arista);
            delete arista;
            this->vertexes[id]->edges.pop_front();
            this->n_edges--;
        }
        delete this->vertexes[id];
        this->vertexes.erase(id);
        this->n_vertex--;
        return true;
    }

    bool deleteEdge(string start, string end){
        // COMPLETED
        // Vertex do not exist Case: Returns False
        if(this->vertexes.find(start) == this->vertexes.end()){
            return false;
        }
        auto end_vertix = this->vertexes.find(end);
        if (end_vertix == this->vertexes.end()){
            return false;
        }
        // Standard Case: Deletion
        for (auto& arista : this->vertexes[start]->edges){
            if (arista->vertexes[0] == end_vertix->second || arista->vertexes[1] == end_vertix->second){
                this->vertexes[end]->edges.remove(arista);
                this->vertexes[start]->edges.remove(arista);
                delete arista;
                this->n_edges--;
                return true;
            }
        }
        // Edge not found Case
        return false;
    }

    TE &operator()(string start, string end){
        // COMPLETED
        // Vertex do not exist Case: Returns False
        if(this->vertexes.find(start) == this->vertexes.end()){
            throw "Vertix not found in the graph";
        }
        auto end_vertix = this->vertexes.find(end);
        if (end_vertix == this->vertexes.end()){
            throw "Vertix not found in the graph";
        }
        // Standard Case: Search and return
        for (auto& arista : this->vertexes[start]->edges){
            if (arista->vertexes[0] == end_vertix->second || arista->vertexes[1] == end_vertix->second){
                return arista->weight;
            }
        }
        // Not found case:
        throw "Trying to access an edge that does not exist";
    }

    float density(){
        // Destino debe ser igual a end
        return (2.0*this->n_edges)/(this->n_vertex*(this->n_vertex-1));
    }

    bool isDense(float threshold = 0.5){
        // COMPLETADO
        if(density()>=threshold){
            return true;
        }
        return false;
    }

    bool isConnected(){
        // TODO
        return false;
    }

    bool isStronglyConnected(){
        // TODO
        return false;
    }

    bool empty(){
        // COMPLETED
        if(this->n_edges == 0){
            return true;
        }
        return false;
    }

    void clear(){
        // COMPLETED
        // Liberacion de memoria
        for(auto& vertex: this->vertexes){
            while (! vertex.second->edges.empty() ){
                auto arista = vertex.second->edges.front();
                auto other = (arista->vertexes[0] == vertex.second ) ? arista->vertexes[1] : arista->vertexes[0];
                other->edges.remove(arista);
                delete arista;
                vertex.second->edges.pop_front();
            }
            delete vertex.second;
        }
        // Reset a valores vacios
        this->n_edges = 0;
        this->n_vertex = 0;
        this->vertexes.clear();
    }

    void displayVertex(string id){
        // COMPLETED
        if(this->vertexes.find(id) == this->vertexes.end()) throw("No existe vertice");
        std::cout << this->vertexes[id]->data << std::endl;
    }

    bool findById(string id){
        // COMPLETED
        return this->vertexes.find(id) != this->vertexes.end();
    }

    void display(){
        // COMPLETED
        cout << "------Listas de adyasencia------" << endl;
        for(auto &vertex : this->vertexes){
            cout<<vertex.second->data<<"\t| ";
            for(auto &edge : vertex.second->edges){
                cout<<"("; if (edge->vertexes[0] == vertex.second) {cout <<edge->vertexes[1]->data;} else {cout <<edge->vertexes[0]->data;}; cout <<","<<edge->weight<<")"<<"\t";
            }
            cout<<endl;
        }
        cout << "--------------------------------" << endl;
    }
};

#endif