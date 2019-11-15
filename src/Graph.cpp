#include "Graph.hpp"

Graph::Graph(uint16_t amountOfVertices) {
    this->adjacencyLists = std::vector<std::list<uint16_t>>(amountOfVertices, std::list<uint16_t>());
}

Graph::~Graph() = default;

void Graph::addEdge(uint16_t from, uint16_t to) {
    this->adjacencyLists[from - 1].push_back(to - 1);
}
