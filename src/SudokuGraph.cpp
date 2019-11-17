#include <cmath>
#include <iostream>
#include "SudokuGraph.hpp"
#include "Vertice.hpp"

SudokuGraph::SudokuGraph(uint32_t tableSize, uint32_t columns, uint32_t rows) {
    this->tableSize = tableSize;
    this->quadrantColumnWidth = columns;
    this->quadrantRowHeight = rows;
    this->amountOfColumns = columns * rows;
    this->amountOfRows = columns * rows;
    const uint32_t amountOfVertices = pow(tableSize, 2);
    this->adjacencyLists = std::vector<std::set<uint32_t>>(amountOfVertices, std::set<uint32_t>());
    for (uint32_t vertice = 0; vertice < amountOfVertices; vertice++) {
        std::cout << "Processing vertice " << vertice << std::endl;
        addEdgesToVerticesInSameColumn(vertice);
        addEdgesToVerticesInSameRow(vertice);
        addEdgesToVerticesInSameQuadrant(vertice);
        std::cout << "Added " << this->adjacencyLists[vertice].size() << " neighbors." << std::endl;
    }
}

SudokuGraph::~SudokuGraph() = default;

void SudokuGraph::addEdge(uint32_t from, uint32_t to) {
    this->adjacencyLists[from].insert(to);
}

uint32_t SudokuGraph::getColumns() {
    return this->quadrantColumnWidth;
}

uint32_t SudokuGraph::getRows() {
    return this->quadrantRowHeight;
}

void SudokuGraph::addEdgesToVerticesInSameColumn(uint32_t verticeIndex) {
    uint32_t verticeColumn = getVerticeColumn(verticeIndex);
    for (uint32_t i = 0; i < amountOfColumns; i++) {
        uint32_t offset = i * amountOfColumns;
        uint32_t neighborIndex = offset + verticeColumn;
        if (neighborIndex == verticeIndex) {
            continue;
        }
        this->addEdge(verticeIndex, neighborIndex);
    }
}

uint32_t SudokuGraph::getVerticeColumn(uint32_t verticeIndex) const {
    return verticeIndex % amountOfColumns;
}

uint32_t SudokuGraph::getVerticeRow(uint32_t verticeIndex) const {
    return verticeIndex / amountOfColumns;
}

void SudokuGraph::addEdgesToVerticesInSameRow(uint32_t verticeIndex) {
    uint32_t rowSize = amountOfColumns;
    uint32_t rowBeginning = verticeIndex - this->getVerticeColumn(verticeIndex);
    uint32_t rowEnd = rowBeginning + rowSize;
    for (uint32_t i = rowBeginning; i < rowEnd; i++) {
        if (i == verticeIndex) {
            continue;
        }
        this->addEdge(verticeIndex, i);
    }
}

void SudokuGraph::addEdgesToVerticesInSameQuadrant(uint32_t verticeIndex) {
    uint32_t verticeColumn = getVerticeColumn(verticeIndex);

    uint32_t quadrantStartColumn = verticeColumn / quadrantRowHeight * quadrantColumnWidth;
    uint32_t quadrantEndColumn = quadrantStartColumn + quadrantColumnWidth;

    uint32_t verticeRow = getVerticeRow(verticeIndex);
    uint32_t quadrantStartRow = verticeRow / quadrantRowHeight * quadrantColumnWidth;
    uint32_t quadrantEndRow = quadrantStartRow + quadrantRowHeight;

    for (uint32_t row = quadrantStartRow; row < quadrantEndRow; row++) {
        uint32_t offset = row * amountOfColumns;
        for (uint32_t col = quadrantStartColumn; col < quadrantEndColumn; col++) {
            uint32_t neighborIndex = offset + col;
            if (neighborIndex == verticeIndex) {
                continue;
            }
            this->addEdge(verticeIndex, neighborIndex);
        }
    }
}


