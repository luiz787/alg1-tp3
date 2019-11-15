#include "SudokuGraph.hpp"

SudokuGraph::SudokuGraph(uint16_t columns, uint16_t rows) {
    this->columns = columns;
    this->rows = rows;
    const uint32_t amountOfVertices = columns * rows;
    this->adjacencyLists = std::vector<std::list<uint16_t>>(amountOfVertices, std::list<uint16_t>());
    for (uint32_t vertice = 0; vertice < amountOfVertices; vertice++) {
        addEdgesToVerticesInSameColumn(vertice);
        addEdgesToVerticesInSameRow(vertice);
        addEdgesToVerticesInSameQuadrant(vertice);
    }
}

SudokuGraph::~SudokuGraph() = default;

void SudokuGraph::addEdge(uint16_t from, uint16_t to) {
    this->adjacencyLists[from - 1].push_back(to - 1);
}

uint32_t SudokuGraph::getColumns() {
    return this->columns;
}

uint32_t SudokuGraph::getRows() {
    return this->rows;
}

void SudokuGraph::addEdgesToVerticesInSameColumn(uint32_t vertice) {
    // TODO: implementar.
}

void SudokuGraph::addEdgesToVerticesInSameRow(uint32_t vertice) {
    uint32_t rowSize = columns;
    uint32_t rowBeginning = (vertice / rowSize * rows) + 1;
    uint32_t rowEnd = rowBeginning + rowSize;
    for (uint32_t i = rowBeginning; i <= rowEnd; i++) {
        this->addEdge(vertice, i);
    }
}

void SudokuGraph::addEdgesToVerticesInSameQuadrant(uint32_t vertice) {
    // TODO: implementar.
}
