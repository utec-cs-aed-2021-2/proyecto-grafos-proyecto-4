#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "../DirectedGraph.h"
#include "../UndirectedGraph.h"
#include <queue>


template <typename TV, typename TE>
Graph<TV, TE>* kruskal(Graph<TV,TE>* grafo){
    auto edges = grafo->getAllEdges();
    std::priority_queue<Edge<TV, TE>*, std::vector<Edge<TV, TE>*>, std::greater<Edge<TV, TE>*>> {edges};
}

#endif