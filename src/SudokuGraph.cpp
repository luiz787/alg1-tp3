#include <cmath>
#include <iostream>
#include <algorithm>
#include "SudokuGraph.hpp"
#include "Vertice.hpp"

SudokuGraph::SudokuGraph(uint32_t problemInstanceSize, uint32_t columns, uint32_t rows, const std::vector<Vertice*>& vertices) {
    this->vertices = vertices;
    this->tableSize = problemInstanceSize;
    this->quadrantColumnWidth = columns;
    this->quadrantRowHeight = rows;
    this->amountOfColumns = columns * rows;
    this->amountOfRows = columns * rows;
    const uint32_t amountOfVertices = pow(problemInstanceSize, 2);
    this->adjacencyLists = std::vector<std::set<uint32_t>>(amountOfVertices, std::set<uint32_t>());
    for (uint32_t vertice = 0; vertice < amountOfVertices; vertice++) {
        addEdgesToVerticesInSameColumn(vertice);
        addEdgesToVerticesInSameRow(vertice);
        addEdgesToVerticesInSameQuadrant(vertice);
        removeAssignedColorFromPeers(vertices[vertice]);
    }
}

void SudokuGraph::computeSaturation() const {
    for (uint32_t i = 0; i < vertices.size(); i++) {
        auto vertice = vertices[i];
        auto adjacencyList = adjacencyLists[i];

        uint32_t saturationDegree = 0;
        auto seenColors = std::set<uint32_t>();
        seenColors.insert(0);
        for (auto neighborIndex : adjacencyList) {
            auto neighbor = vertices[neighborIndex];
            auto neighborColor = neighbor->getValue();
            if (seenColors.find(neighborColor) == seenColors.end()) {
                saturationDegree++;
                seenColors.insert(neighborColor);
            }
        }
        vertice->setSaturation(saturationDegree);
    }
}

SudokuGraph::~SudokuGraph() = default;

void SudokuGraph::addEdge(uint32_t from, uint32_t to) {
    this->adjacencyLists[from].insert(to);
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
        auto verticeValue = vertices[verticeIndex]->getValue();
        if (verticeValue != 0) { // vertice already contains a value.
            auto verticeColor = vertices[verticeIndex]->getFinalColor();

            auto neighbor = vertices[neighborIndex];
            neighbor->removeColorPossibility(verticeColor);
        }
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
        auto verticeValue = vertices[verticeIndex]->getValue();
        if (verticeValue != 0) { // vertice already contains a value.
            auto verticeColor = vertices[verticeIndex]->getFinalColor();
            auto neighbor = vertices[i];
            neighbor->removeColorPossibility(verticeColor);
        }
    }
}

void SudokuGraph::addEdgesToVerticesInSameQuadrant(uint32_t verticeIndex) {
    uint32_t verticeColumn = getVerticeColumn(verticeIndex);

    uint32_t entireQuadrantsToLeft = verticeColumn / quadrantColumnWidth;
    uint32_t quadrantStartColumn = entireQuadrantsToLeft * quadrantColumnWidth;
    uint32_t quadrantEndColumn = quadrantStartColumn + quadrantColumnWidth;

    uint32_t verticeRow = getVerticeRow(verticeIndex);
    uint32_t entireQuadrantsAbove = verticeRow / quadrantRowHeight;

    uint32_t quadrantStartRow = entireQuadrantsAbove * quadrantRowHeight;
    uint32_t quadrantEndRow = quadrantStartRow + quadrantRowHeight;

    for (uint32_t row = quadrantStartRow; row < quadrantEndRow; row++) {
        uint32_t offset = row * amountOfColumns;
        for (uint32_t col = quadrantStartColumn; col < quadrantEndColumn; col++) {
            uint32_t neighborIndex = offset + col;
            if (neighborIndex == verticeIndex) {
                continue;
            }
            this->addEdge(verticeIndex, neighborIndex);
            auto verticeValue = vertices[verticeIndex]->getValue();
            if (verticeValue != 0) { // vertice already contains a value.
                auto verticeColor = vertices[verticeIndex]->getFinalColor();
                auto neighbor = vertices[neighborIndex];
                neighbor->removeColorPossibility(verticeColor);
            }
        }
    }
}

void SudokuGraph::tryToAssignColorByCheckingQuadrantExhaustion(const uint32_t verticeIndex,uint32_t &totalColoredVertices,
                                                               uint32_t &verticesThatGainedColorsInCurrentIteration) {
    uint32_t verticeColumn = getVerticeColumn(verticeIndex);

    uint32_t entireQuadrantsToLeft = verticeColumn / quadrantColumnWidth;
    uint32_t quadrantStartColumn = entireQuadrantsToLeft * quadrantColumnWidth;
    uint32_t quadrantEndColumn = quadrantStartColumn + quadrantColumnWidth;

    uint32_t verticeRow = getVerticeRow(verticeIndex);
    uint32_t entireQuadrantsAbove = verticeRow / quadrantRowHeight;

    uint32_t quadrantStartRow = entireQuadrantsAbove * quadrantRowHeight;
    uint32_t quadrantEndRow = quadrantStartRow + quadrantRowHeight;

    auto unassignedNeighbors = std::set<Vertice*>();

    for (uint32_t row = quadrantStartRow; row < quadrantEndRow; row++) {
        uint32_t offset = row * amountOfColumns;
        for (uint32_t col = quadrantStartColumn; col < quadrantEndColumn; col++) {
            uint32_t neighborIndex = offset + col;
            if (neighborIndex == verticeIndex) {
                continue;
            }
            auto neighbor = vertices[neighborIndex];
            if (neighbor->getValue() == 0) {
                unassignedNeighbors.insert(neighbor);
            }
        }
    }
    auto currentVertice = vertices[verticeIndex];
    tryViaExhaustion(totalColoredVertices, verticesThatGainedColorsInCurrentIteration, unassignedNeighbors,
                     currentVertice);
}

void SudokuGraph::solve() {
    uint32_t totalColoredVertices = 0;
    auto copyVertices = std::vector<Vertice*>();
    std::copy(vertices.begin(), vertices.end(), std::back_inserter(copyVertices));
    for (auto& vertice : copyVertices) {
        if (vertice->getValue() != 0) {
            totalColoredVertices++;
        }
    }
    uint32_t verticesThatGainedColorsInCurrentIteration;
    do {
        verticesThatGainedColorsInCurrentIteration = 0;
        computeSaturation();
        std::sort(copyVertices.begin(), copyVertices.end(), Vertice::compareVerticesByDescendingSaturation);
        assignColorToSaturatedVertices(copyVertices, totalColoredVertices, verticesThatGainedColorsInCurrentIteration);
        assignColorToExhaustedUnit(totalColoredVertices, verticesThatGainedColorsInCurrentIteration);
    } while (verticesThatGainedColorsInCurrentIteration > 0);
    printAnswer(totalColoredVertices);
}

void SudokuGraph::assignColorToExhaustedUnit(uint32_t &totalColoredVertices,
                                             uint32_t &verticesThatGainedColorsInCurrentIteration) {
    for (auto& vertice : vertices) {
        if (vertice->getQuantityOfPossibleColors() > 1 && vertice->getValue() == 0) {
            tryToAssignColorByCheckingQuadrantExhaustion(vertice->getIndex(), totalColoredVertices, verticesThatGainedColorsInCurrentIteration);
            tryToAssignColorByCheckingRowExhaustion(vertice->getIndex(), totalColoredVertices, verticesThatGainedColorsInCurrentIteration);
            tryToAssignColorByCheckingColumnExhaustion(vertice->getIndex(), totalColoredVertices, verticesThatGainedColorsInCurrentIteration);
        }
    }
}

void SudokuGraph::assignColorToSaturatedVertices(const std::vector<Vertice *> &copyVertices, uint32_t &totalColoredVertices,
                                            uint32_t &verticesThatGainedColorsInCurrentIteration) {
    for (auto& vertice : copyVertices) {
        if (vertice->getQuantityOfPossibleColors() == 1 && vertice->getValue() == 0) {
            auto color = *vertice->getPossibleColors().begin();

            vertice->updateValue(static_cast<int>(color));
            vertice->setFinalColor(color);

            removeAssignedColorFromPeers(vertice);
            verticesThatGainedColorsInCurrentIteration++;
            totalColoredVertices++;
        }
    }
}

void SudokuGraph::printAnswer(const uint32_t totalColoredVertices) const {
    if (totalColoredVertices < vertices.size()) {
        std::cout << "sem ";
    }
    std::cout << "solução" << std::endl;
    for (uint32_t i = 0; i < amountOfRows; i++) {
        const uint32_t offset = i * amountOfColumns;
        for (uint32_t j = 0; j < amountOfColumns; j++) {
            std::cout << vertices[offset + j]->getValue() << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Colori " << totalColoredVertices << std::endl;
}

void SudokuGraph::removeAssignedColorFromPeers(Vertice *vertice) {
    auto assignedColor = Color(vertice->getValue());
    auto peersIndexes = adjacencyLists[vertice->getIndex()];
    for (auto peerIndex : peersIndexes) {
        vertices[peerIndex]->removeColorPossibility(assignedColor);
    }
}

void SudokuGraph::tryToAssignColorByCheckingRowExhaustion(uint32_t verticeIndex, uint32_t &totalColoredVertices,
                                                          uint32_t &verticesThatGainedColorsInCurrentIteration) {
    uint32_t rowSize = amountOfColumns;
    uint32_t rowBeginning = verticeIndex - this->getVerticeColumn(verticeIndex);
    uint32_t rowEnd = rowBeginning + rowSize;
    auto unassignedNeighbors = std::set<Vertice*>();
    for (uint32_t i = rowBeginning; i < rowEnd; i++) {
        if (i == verticeIndex) {
            continue;
        }
        auto neighbor = vertices[i];
        if (neighbor->getValue() == 0) {
            unassignedNeighbors.insert(neighbor);
        }

    }

    auto currentVertice = vertices[verticeIndex];
    tryViaExhaustion(totalColoredVertices, verticesThatGainedColorsInCurrentIteration, unassignedNeighbors,
                     currentVertice);
}

void SudokuGraph::tryViaExhaustion(uint32_t &totalColoredVertices, uint32_t &verticesThatGainedColorsInCurrentIteration,
                                   const std::set<Vertice *> &unassignedNeighbors, Vertice *currentVertice) {
    if (currentVertice->getValue() != 0) {
        return; // The vertice could already have a value...
    }
    auto currentVerticePossibleColors = currentVertice->getPossibleColors();
    for (auto color : currentVerticePossibleColors) {
        bool someNeighborCanBeOfColor = false;
        for (auto neighbor : unassignedNeighbors) {
            auto possibleNeighborColors = neighbor->getPossibleColors();
            bool contains = possibleNeighborColors.find(color) != possibleNeighborColors.end();
            if (contains) {
                someNeighborCanBeOfColor = true;
                break;
            }
        }

        if (!someNeighborCanBeOfColor) {
            std::cout << "Found potential match. Vertice index " << currentVertice->getIndex()
                      << "can be " << static_cast<int>(color) << " but none of its quadrant neighbors can." << std::endl;
            currentVertice->setFinalColor(color);
            verticesThatGainedColorsInCurrentIteration++;
            totalColoredVertices++;
            currentVertice->updateValue(static_cast<int>(color));
            removeAssignedColorFromPeers(currentVertice);
            break;
        }
    }
}

void SudokuGraph::tryToAssignColorByCheckingColumnExhaustion(uint32_t verticeIndex, uint32_t &totalColoredVertices,
                                                             uint32_t &verticesThatGainedColorsInCurrentIteration) {
    uint32_t verticeColumn = getVerticeColumn(verticeIndex);
    auto unassignedNeighbors = std::set<Vertice*>();
    for (uint32_t i = 0; i < amountOfColumns; i++) {
        uint32_t offset = i * amountOfColumns;
        uint32_t neighborIndex = offset + verticeColumn;
        if (neighborIndex == verticeIndex) {
            continue;
        }
        auto neighbor = vertices[neighborIndex];
        if (neighbor->getValue() == 0) {
            unassignedNeighbors.insert(neighbor);
        }
    }

    auto currentVertice = vertices[verticeIndex];
    tryViaExhaustion(totalColoredVertices, verticesThatGainedColorsInCurrentIteration, unassignedNeighbors,
                     currentVertice);
}
