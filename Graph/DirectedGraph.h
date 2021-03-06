#ifndef NONDIRECTEDGRAPH_H
#define NONDIRECTEDGRAPH_H

#include <stack>
#include "graph.h"

template<typename TV, typename TE>
class DirectedGraph : public Graph<TV, TE>{


public:
    DirectedGraph() = default;

    ~DirectedGraph(){
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
        arista->vertexes[0] = this->vertexes[id1]; // vertex0 = OUT VERTEX (origin)
        arista->vertexes[1] = this->vertexes[id2]; // vertex1 = IN VERTEX (destiny)
        arista->weight = w;
        this->n_edges++;
        this->vertexes[id1]->edges.push_back(arista);
        this->vertexes[id2]->edges.push_back(arista);
        // Se inserta puntero a la arista tambient en el vertice de destinopara una
        // complejidad reducida en las operaciones de borrado de vertices en el caso promedio
        // a cambio de un leve incremento en memoria (tradeoff memoria-tiempo)
        // Se considera que este es un tradeoff favorable considerando que se esta trabajando
        // sobre una matriz de dimensiones dinamica, con lo que la eliminacion de nodos
        // sera una operacion frecuente
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
            if (arista->vertexes[1] == end_vertix->second){ // Destino debe ser igual a end
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
            if (arista->vertexes[1] == end_vertix->second){ // Destino debe ser igual a end
                return arista->weight;
            }
        }
        // Not found case:
        throw "Trying to access an edge that does not exist";
    }

    float density(){
        // Destino debe ser igual a end
        return ((float) this->n_edges)/(this->n_vertex*(this->n_vertex-1));
    }

    bool isDense(float threshold = 0.5){
        // Destino debe ser igual a end
        if(density()>=threshold){
            return true;
        }
        return false;
    }

    bool isConnected(){
        // COMPLETE
        // Note: Se esta entendiendo connected en directed graph como
        // weakly connected (Un grafo es weakly connected cuando "si se remplazaran
        // todos las aristas dirigidas por no dirigidas se obtendria un grafo conexo")
        if (this->n_vertex == 0) {return true;}
        // Deep First Search
        // Auxiliar lambda
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
        // Inicializacion de contenedores
        stack<Vertex<TV, TE>*> stk;
        vector<Vertex<TV, TE>*> visited;
        vector<Vertex<TV, TE>*> sol;

        // Loop de exploracion
        stk.push(this->vertexes.begin()->second);
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
        // Comparacion de tama??o para determinar conectividad
        return (this->vertexes.size() == visited.size());
    }

    bool isStronglyConnected(){
        // COMPLETE
        if (this->n_vertex == 0) {return true;}
        // Deep First Search
        // Auxiliar lambda
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
        for (auto it = this->vertexes.begin(); it != this->vertexes.end() ; ++it) {
            // Loop de exploracion
            stack<Vertex<TV, TE>*> stk;
            vector<Vertex<TV, TE>*> visited;
            vector<Vertex<TV, TE>*> sol;

            stk.push(it->second);

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
            // Comparacion de tama??o para determinar conectividad
            if (this->vertexes.size() != visited.size()) {return false;}
        }
        // Cumple en todos los casos
        return true;
    }

    bool empty(){
        // Destino debe ser igual a end
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
            cout<<vertex.second->data <<"\t| ";
            for(auto &edge : vertex.second->edges){
                if (edge->vertexes[0] == vertex.second) {
                    cout<<"("<<edge->vertexes[1]->data<<","<<edge->weight<<")"<<" \t";
                }
            }
            cout<<endl;
        }
        cout << "--------------------------------" << endl;
    }
};

#endif