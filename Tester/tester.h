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
        // Is Empty
        std::cout << "Is Empty?:"; if (graph->empty()){std::cout <<"True";} else {std::cout <<"False";} ;std::cout << std::endl;
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
        graph->createEdge("C", "B", 7.5);
        graph->createEdge("B", "E", 1.1);
        graph->createEdge("D", "B", 0.3);
        graph->createEdge("C", "D", 5.4);
        graph->createEdge("E", "C", 1.0);

        graph->display();
        // Density
        std::cout << "Density:" << graph->density() << std::endl;
        // Is Dense
        std::cout << "Is Dense?:"; if (graph->isDense()){std::cout <<"True";} else {std::cout <<"False";} ;std::cout << std::endl;
        // Is connected
        std::cout << "Is Connected?:"; if (graph->isConnected()){std::cout <<"True";} else {std::cout <<"False";} ;std::cout << std::endl;
        // Is strongly connected
        std::cout << "Is Strongly Connected?:"; if (graph->isStronglyConnected()){std::cout <<"True";} else {std::cout <<"False";} ;std::cout << std::endl;
        // Is Empty
        std::cout << "Is Empty?:"; if (graph->empty()){std::cout <<"True";} else {std::cout <<"False";} ;std::cout << std::endl;
    }
}

#endif //PROYECTO_GRAFOS_PROYECTO_4_TESTER_H
