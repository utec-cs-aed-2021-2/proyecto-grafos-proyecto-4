//
// Created by Rodrigo on 15/11/2021.
//

#ifndef PROYECTO_GRAFOS_PROYECTO_4_TESTER_H
#define PROYECTO_GRAFOS_PROYECTO_4_TESTER_H

#include <string>
#include "Graph/DirectedGraph.h"
#include "Graph/UndirectedGraph.h"

namespace Tester{
    void executeExamples();

    template <template <typename, typename > class G>
    void graphSimulation() {
        // Constructor
        Graph<std::string, float>* graph = new G<std::string, float>{};
        graph->display();
        // Insert Vertex
        graph->insertVertex("A", "Lima");
        graph->insertVertex("B", "Callao");
        graph->insertVertex("C", "Cuzco");
        graph->insertVertex("D", "Ica");
        graph->insertVertex("E", "Junin");
        graph->display();
        // Create Edge
        graph->createEdge("A", "C", 7.5);
        graph->createEdge("A", "B", 0.2);
        graph->createEdge("A", "D", 1.5);
        graph->createEdge("E", "A", 1.7);
        graph->display();
        //

    }
}

#endif //PROYECTO_GRAFOS_PROYECTO_4_TESTER_H
