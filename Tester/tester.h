//
// Created by Rodrigo on 15/11/2021.
//

#ifndef PROYECTO_GRAFOS_PROYECTO_4_TESTER_H
#define PROYECTO_GRAFOS_PROYECTO_4_TESTER_H

#include <string>
#include "Graph/DirectedGraph.h"
#include "Graph/UndirectedGraph.h"
#include "Graph/Algorithms/bfs.h"
#include "Graph/Algorithms/dfs.h"
#include "Graph/Algorithms/prim.h"
#include "Graph/Algorithms/kruskal.h"

namespace Tester{
    void executeExamples();

    template <typename G>
    void displayStats(G graph){
        // Is Empty
        std::cout << "Is Empty?:"; if (graph->empty()){std::cout <<"True";} else {std::cout <<"False";} ;std::cout << std::endl;
        // Density
        std::cout << "Density:" << graph->density() << std::endl;
        // Is Dense
        std::cout << "Is Dense?:"; if (graph->isDense()){std::cout <<"True";} else {std::cout <<"False";} ;std::cout << std::endl;
        // Is connected
        std::cout << "Is Connected?:"; if (graph->isConnected()){std::cout <<"True";} else {std::cout <<"False";} ;std::cout << std::endl;
        // Is strongly connected
        std::cout << "Is Strongly Connected?:"; if (graph->isStronglyConnected()){std::cout <<"True";} else {std::cout <<"False";} ;std::cout << std::endl;
    }

    template <template <typename, typename > class G>
    void graphSimulation() {
        // Constructor
        auto graph = new G<std::string, float>{};
        // Stats & display
        graph->display();
        displayStats(graph);
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
        // Stats & display
        graph->display();
        displayStats(graph);
        // Remove Vertex
        graph->deleteVertex("A");
        graph->deleteVertex("E");
        // Stats & display
        graph->display();
        displayStats(graph);
        // Remove Edge
        graph->deleteEdge("C", "D");
        // Stats & display
        graph->display();
        displayStats(graph);
        // Update Edge
        graph->operator()("C", "B")=8.0;
        // Stats & display
        graph->display();
        displayStats(graph);
        // Clear
        graph->clear();
        // Stats & display
        graph->display();
        displayStats(graph);


        // Algorithm examples
        graph->insertVertex("1", "A");
        graph->insertVertex("2", "B");
        graph->insertVertex("3", "C");
        graph->insertVertex("4", "D");
        graph->insertVertex("5", "E");
        graph->insertVertex("6", "F");
        graph->insertVertex("7", "G");

        graph->createEdge("1", "2", 0.5);
        graph->createEdge("1", "3", 0.5);
        graph->createEdge("3", "4", 0.5);
        graph->createEdge("2", "5", 0.5);
        graph->createEdge("5", "6", 0.5);
        graph->createEdge("4", "6", 0.5);
        graph->createEdge("6", "7", 0.5);
        // Stats & display
        graph->display();
        displayStats(graph);
        // BFS
        cout << "BFS:" << endl;
        auto ans_bfs = bfs(graph, "1");
        for (auto &vertix : ans_bfs) {
            cout << vertix->data << endl;
        }
        // DFS
        cout << "DFS:" << endl;
        auto ans_dfs = dfs(graph, "1");
        for (auto &vertix : ans_dfs) {
            cout << vertix->data << endl;
        }

        // Destructor
        delete graph;

    }
}

#endif //PROYECTO_GRAFOS_PROYECTO_4_TESTER_H
