//
// Created by Rodrigo on 15/11/2021.
//

#include <iostream>
#include "tester.h"

void Tester::executeExamples() {
    std::cout << "================================================" << std::endl;
    std::cout << "Undirected Graph" << std::endl;
    std::cout << "================================================" << std::endl;
    graphSimulation<UnDirectedGraph>();
    std::cout << "================================================" << std::endl;
    std::cout << "Directed Graph" << std::endl;
    std::cout << "================================================" << std::endl;
    graphSimulation<DirectedGraph>();
}