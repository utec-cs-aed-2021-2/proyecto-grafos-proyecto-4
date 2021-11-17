//
// Created by Rodrigo on 15/11/2021.
//

#include <iostream>
#include "tester.h"

void Tester::executeExamples() {
    std::cout << std::endl << std::endl;
    std::cout << "================================================" << std::endl;
    std::cout << "Directed Graph" << std::endl;
    std::cout << "================================================" << std::endl;
    graphSimulation<DirectedGraph>();
    std::cout << std::endl << std::endl;
    std::cout << "================================================" << std::endl;
    std::cout << "Undirected Graph" << std::endl;
    std::cout << "================================================" << std::endl;
    graphSimulation<UnDirectedGraph>();
    std::cout << std::endl << std::endl;
    std::cout << "================================================" << std::endl;
    std::cout << "MST Alogirthms" << std::endl;
    std::cout << "================================================" << std::endl;
    MSTAlgoDemo();
}


void Tester::MSTAlgoDemo() {
    // =============================
    // MST ALGORITHMS TEST
    // =============================

    // Constructor
    auto graph = new UnDirectedGraph<std::string, float>{};
    graph->clear();
    // Algorithm examples
    graph->insertVertex("1", "A");
    graph->insertVertex("2", "B");
    graph->insertVertex("3", "C");
    graph->insertVertex("4", "D");

    graph->createEdge("1", "2", 5);
    graph->createEdge("1", "3", 10);
    graph->createEdge("1", "4", 3);
    graph->createEdge("2", "4", 20);
    graph->createEdge("4", "3", 2);
    graph->display();
    // Kruskal
    cout << "Kruskal" << endl;
    auto mst_k = kruskal(graph);
    mst_k->display();
    delete mst_k;
    // Prim
    cout << "Prim" << endl;
    auto mst_p = prim(graph, "2");
    mst_p->display();
    delete mst_p;
    graph->clear();

    // Destructor
    delete graph;
}