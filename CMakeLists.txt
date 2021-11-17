cmake_minimum_required(VERSION 3.20)
project(proyecto_grafos_proyecto_4)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Graph)
include_directories(Graph/Algorithms)

add_executable(proyecto_grafos_proyecto_4
        Graph/Algorithms/astar.h
        Graph/Algorithms/bfs.h
        Graph/Algorithms/dfs.h
        Graph/Algorithms/dijkstra.h
        Graph/Algorithms/kruskal.h
        Graph/Algorithms/prim.h
        Graph/DirectedGraph.h
        Graph/graph.h
        Graph/UndirectedGraph.h
        main.cpp
        Tester/tester.cpp Tester/tester.h)
