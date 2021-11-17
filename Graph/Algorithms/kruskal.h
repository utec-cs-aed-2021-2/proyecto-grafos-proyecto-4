#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "../DirectedGraph.h"
#include "../UndirectedGraph.h"
#include <vector>
#include <queue>
#include <unordered_map>
template <typename E>
struct greater_edge{
    bool operator()(E le,E re){
        return (*le)>(*re);
    }
};

template <typename V>
V getSetParent(std::unordered_map<V, V> &set, V vertex) {
    while (set.find(vertex) != set.end()){
        auto parent = getSetParent(set, set[vertex]);
        set[vertex] = parent;
        return parent;
    }
    return vertex;
}

template <typename V>
void unionSet(std::unordered_map<V, V> &set, V v1, V v2) {
    v1 = getSetParent(set, v1);
    v2 = getSetParent(set, v2);
    set[v1] = v2;
}

template <typename TV, typename TE>
Graph<TV, TE>* kruskal(DirectedGraph<TV,TE>* grafo){
    throw("Kruksal does not work with directed graphs");
}

template <typename TV, typename TE>
Graph<TV, TE>* kruskal(UnDirectedGraph<TV,TE>* grafo){
    // Solution
    auto solution = new UnDirectedGraph<TV, TE>{};
    // Heap
    auto edges = grafo->getAllEdges();
    std::make_heap(edges.begin(), edges.end(), greater_edge<Edge<TV, TE>*>{});
    // Set (representado mediante hash)
    unordered_map<Vertex<TV, TE>*, Vertex<TV, TE>*> set;

    // Loop
    for (int i = 0; i < edges.size(); ++i) {
        // Break condition
        if (solution->getNumberEdges() >= grafo->getNumberVertexes()-1) {
            break;
        }
        // Pop from queue
        auto arista = edges.front();
        std::pop_heap(edges.begin(), edges.end()-i, greater_edge<Edge<TV, TE>*>{});
        // Check set
        if ((getSetParent(set, arista->vertexes[0])) != getSetParent(set, arista->vertexes[1])){
            // Add edge
            solution->insertVertex(arista->vertexes[0]->data, arista->vertexes[0]->data);
            solution->insertVertex(arista->vertexes[1]->data, arista->vertexes[1]->data);
            solution->createEdge(arista->vertexes[0]->data, arista->vertexes[1]->data, arista->weight);
            // Merge sets
            unionSet(set, arista->vertexes[0], arista->vertexes[1]);
        }
    }

    // Solution
    return solution;

}

#endif