#ifndef PRIM_H
#define PRIM_H

#include "../DirectedGraph.h"
#include "../UndirectedGraph.h"
#include <vector>
#include <unordered_map>
#include <algorithm>

template <typename TV, typename TE>
struct VertexDistance{
    Vertex<TV, TE>* vertex;
    TE distance{};
    bool infinite;
    Vertex<TV, TE>* parent= nullptr;

    explicit VertexDistance(Vertex<TV, TE>* v) {
        vertex = v;
        infinite = true;
        parent = nullptr;
    }

    VertexDistance(Vertex<TV, TE>* v, TE d) {
        vertex = v;
        distance = d;
        infinite = false;
        parent = nullptr;
    }

    bool operator>(TE val){
        if (infinite) {
            return true;
        }
        return (distance > val);
    }

    bool operator==(Vertex<TV, TE>* v){
        return (v==vertex);
    }
};

template <typename TV, typename TE>
bool operator>(const VertexDistance<TV, TE> &v1, const VertexDistance<TV, TE> &v2){
    if (v1.infinite) {
        return true;
    }
    if (v2.infinite) {
        return false;
    }
    return (v1.distance > v2.distance);
}

template <typename TV, typename TE>
Graph<TV, TE>* prim(DirectedGraph<TV,TE>* grafo, string id){
    throw("Prim does not work with directed graphs");
}

template <typename TV, typename TE>
Graph<TV, TE>* prim(UnDirectedGraph<TV,TE>* grafo, string id){
    // Solution
    auto solution = new UnDirectedGraph<TV, TE>{};
    // Priority queue
    auto vertexes = grafo->getAllVertex();
    auto start = grafo->getVertex(id);
    std::vector<VertexDistance<TV, TE>> pq;
    for (auto &v : vertexes) {
        if (v == start) {
            pq.push_back(VertexDistance<TV, TE>(v,0));
        }
        else {
            pq.push_back(VertexDistance<TV, TE>(v));
        }
        // Add vertexes to graph
        solution->insertVertex(v->data, v->data);
    }
    std::make_heap(pq.begin(), pq.end(), greater<VertexDistance<TV, TE>>{});
    // Loop
    for (int i = 0; i < pq.size(); ++i) {
        // Pop from queue
        auto vd = pq.front();
        std::pop_heap(pq.begin(), pq.end()-i, greater<VertexDistance<TV, TE>>{});
        // Loop over edges
        for (auto &edge : vd.vertex->edges) {
            // Get other
            auto other = (edge->vertexes[0] == vd.vertex ) ? edge->vertexes[1] : edge->vertexes[0];
            auto v = std::find(pq.begin(), pq.end()-i-1, other);
            // Validate if v still not explred
            if (v != pq.end()-i-1){
                // Validate if distance > weight
                if (v->distance > edge->weight or v->infinite){
                    // Update edge
                    v->parent = vd.vertex;
                    v->distance = edge->weight;
                    v->infinite = false;
                    std::make_heap(pq.begin(), pq.end()-i-1, greater<VertexDistance<TV, TE>>{});
                }
            }

        }
    }
    // Solution
    for (auto &e : pq) {
        if (e.parent != nullptr){
            // Add new edge
            solution->createEdge(e.vertex->data, e.parent->data, e.distance);
        }
    }
    return solution;
}

#endif