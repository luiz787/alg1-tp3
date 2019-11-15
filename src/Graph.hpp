#ifndef ALG1_TP3_GRAPH_HPP
#define ALG1_TP3_GRAPH_HPP

#include <cstdint>
#include <list>
#include <vector>

class Graph {
private:
    std::vector<std::list<uint16_t>> adjacencyLists;
public:
    explicit Graph(uint16_t amountOfVertices);
    ~Graph();
    void addEdge(uint16_t from, uint16_t to);
};

#endif
