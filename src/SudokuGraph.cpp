#include <iostream>
#include "SudokuGraph.hpp"
#include "Vertice.hpp"

SudokuGraph::SudokuGraph(const uint32_t columns, const uint32_t rows, const std::vector<Vertice *> &vertices)
        : quadrantColumnWidth(columns), quadrantRowHeight(rows), amountOfColumns(columns * rows),
        amountOfRows(columns * rows) {
    this->vertices = vertices;
    for (auto vertice : this->vertices) {
        addEdgesToVerticesInSameColumn(vertice);
        addEdgesToVerticesInSameRow(vertice);
        addEdgesToVerticesInSameQuadrant(vertice);
        removeAssignedColorFromNeighbors(vertice);
    }
}

SudokuGraph::~SudokuGraph() = default;

void SudokuGraph::addEdgesToVerticesInSameColumn(Vertice *vertice) {
    const auto verticeIndex = vertice->getIndex();
    const uint32_t verticeColumn = getVerticeColumn(verticeIndex);
    for (uint32_t i = 0; i < amountOfColumns; i++) {
        const uint32_t offset = i * amountOfColumns;
        const uint32_t neighborIndex = offset + verticeColumn;
        if (neighborIndex == verticeIndex) {
            continue;
        }
        vertice->addNeighbor(neighborIndex);
        vertice->addColumnNeighbor(neighborIndex);
        if (vertice->isColored()) {
            const auto verticeColor = vertice->getColor();

            const auto neighbor = vertices[neighborIndex];
            neighbor->removeColorPossibility(verticeColor);
        }
    }
}

uint32_t SudokuGraph::getVerticeColumn(const uint32_t verticeIndex) const {
    return verticeIndex % amountOfColumns;
}

uint32_t SudokuGraph::getVerticeRow(const uint32_t verticeIndex) const {
    return verticeIndex / amountOfColumns;
}

void SudokuGraph::addEdgesToVerticesInSameRow(Vertice *vertice) {
    const auto verticeIndex = vertice->getIndex();
    const uint32_t rowSize = amountOfColumns;
    const uint32_t rowBeginning = verticeIndex - this->getVerticeColumn(verticeIndex);
    const uint32_t rowEnd = rowBeginning + rowSize;
    for (uint32_t i = rowBeginning; i < rowEnd; i++) {
        if (i == verticeIndex) {
            continue;
        }
        vertice->addNeighbor(i);
        vertice->addRowNeighbor(i);
        if (vertice->isColored()) {
            const auto verticeColor = vertice->getColor();
            const auto neighbor = vertices[i];
            neighbor->removeColorPossibility(verticeColor);
        }
    }
}

void SudokuGraph::addEdgesToVerticesInSameQuadrant(Vertice *vertice) {
    const auto verticeIndex = vertice->getIndex();
    const uint32_t verticeColumn = getVerticeColumn(verticeIndex);

    const uint32_t entireQuadrantsToLeft = verticeColumn / quadrantColumnWidth;
    const uint32_t quadrantStartColumn = entireQuadrantsToLeft * quadrantColumnWidth;
    const uint32_t quadrantEndColumn = quadrantStartColumn + quadrantColumnWidth;

    const uint32_t verticeRow = getVerticeRow(verticeIndex);
    const uint32_t entireQuadrantsAbove = verticeRow / quadrantRowHeight;

    const uint32_t quadrantStartRow = entireQuadrantsAbove * quadrantRowHeight;
    const uint32_t quadrantEndRow = quadrantStartRow + quadrantRowHeight;

    for (uint32_t row = quadrantStartRow; row < quadrantEndRow; row++) {
        const uint32_t offset = row * amountOfColumns;
        for (uint32_t col = quadrantStartColumn; col < quadrantEndColumn; col++) {
            const uint32_t neighborIndex = offset + col;
            if (neighborIndex == verticeIndex) {
                continue;
            }
            vertice->addNeighbor(neighborIndex);
            vertice->addQuadrantNeighbor(neighborIndex);
            if (vertice->isColored()) {
                const auto verticeColor = vertice->getColor();
                const auto neighbor = vertices[neighborIndex];
                neighbor->removeColorPossibility(verticeColor);
            }
        }
    }
}

void SudokuGraph::tryToAssignColorByCheckingQuadrantExhaustion(Vertice *vertice, uint32_t &totalColoredVertices,
                                                               uint32_t &verticesThatGainedColorsInCurrentIteration) {
    auto quadrantNeighbors = vertice->getQuadrantNeighbors();
    auto unassignedQuadrantNeighbors = std::set<Vertice*>();
    for (auto quadrantNeighborIndex : quadrantNeighbors) {
        auto quadrantNeighbor = vertices[quadrantNeighborIndex];
        if (!quadrantNeighbor->isColored()) {
            unassignedQuadrantNeighbors.insert(quadrantNeighbor);
        }
    }
    assignColorToVerticeIfPossible(
            vertice, unassignedQuadrantNeighbors, totalColoredVertices, verticesThatGainedColorsInCurrentIteration);
}

void SudokuGraph::solve() {
    uint32_t totalColoredVertices = 0;
    for (auto& vertice : vertices) {
        if (vertice->isColored()) {
            totalColoredVertices++;
        }
    }
    uint32_t verticesThatGainedColorsInCurrentIteration;
    do {
        verticesThatGainedColorsInCurrentIteration = 0;
        assignColorToSaturatedVertices(totalColoredVertices, verticesThatGainedColorsInCurrentIteration);
        assignColorToExhaustedUnits(totalColoredVertices, verticesThatGainedColorsInCurrentIteration);
    } while (verticesThatGainedColorsInCurrentIteration > 0);
    printAnswer(totalColoredVertices);
}

void SudokuGraph::assignColorToExhaustedUnits(uint32_t &totalColoredVertices,
                                              uint32_t &verticesThatGainedColorsInCurrentIteration) {
    for (auto& vertice : vertices) {
        if (vertice->getAmountOfPossibleColors() > 1 && !vertice->isColored()) {
            tryToAssignColorByCheckingQuadrantExhaustion(vertice, totalColoredVertices, verticesThatGainedColorsInCurrentIteration);
            tryToAssignColorByCheckingRowExhaustion(vertice, totalColoredVertices, verticesThatGainedColorsInCurrentIteration);
            tryToAssignColorByCheckingColumnExhaustion(vertice, totalColoredVertices, verticesThatGainedColorsInCurrentIteration);
        }
    }
}

void SudokuGraph::assignColorToSaturatedVertices(uint32_t &totalColoredVertices,
                                                 uint32_t &verticesThatGainedColorsInCurrentIteration) {
    for (auto& vertice : vertices) {
        if (vertice->getAmountOfPossibleColors() == 1 && !vertice->isColored()) {
            const auto color = *vertice->getPossibleColors().begin();

            vertice->updateValue(static_cast<int>(color));
            vertice->setFinalColor(color);

            removeAssignedColorFromNeighbors(vertice);
            ++verticesThatGainedColorsInCurrentIteration;
            ++totalColoredVertices;
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
            auto color = vertices[offset + j]->getColor();
            std::cout << static_cast<uint32_t>(color) << " ";
        }
        std::cout << std::endl;
    }
}

void SudokuGraph::removeAssignedColorFromNeighbors(Vertice *vertice) {
    const auto assignedColor = vertice->getColor();
    const auto neighborsIndexes = vertice->getAdjacencyList();
    for (auto neighborIndex : neighborsIndexes) {
        auto neighbor = vertices[neighborIndex];
        neighbor->removeColorPossibility(assignedColor);
    }
}

void SudokuGraph::tryToAssignColorByCheckingRowExhaustion(Vertice *vertice, uint32_t &totalColoredVertices,
                                                          uint32_t &verticesThatGainedColorsInCurrentIteration) {
    auto rowNeighbors = vertice->getRowNeighbors();
    auto unassignedRowNeighbors = std::set<Vertice*>();
    for (auto rowNeighborIndex : rowNeighbors) {
        auto rowNeighbor = vertices[rowNeighborIndex];
        if (!rowNeighbor->isColored()) {
            unassignedRowNeighbors.insert(rowNeighbor);
        }
    }
    assignColorToVerticeIfPossible(
            vertice, unassignedRowNeighbors, totalColoredVertices, verticesThatGainedColorsInCurrentIteration);
}

void SudokuGraph::assignColorToVerticeIfPossible(Vertice *currentVertice, const std::set<Vertice *> &unassignedNeighbors,
                                                 uint32_t &totalColoredVertices,
                                                 uint32_t &verticesThatGainedColorsInCurrentIteration) {
    if (currentVertice->isColored()) {
        return; // The vertice could already have a color...
    }
    const auto currentVerticePossibleColors = currentVertice->getPossibleColors();
    for (auto color : currentVerticePossibleColors) {
        bool someNeighborCanBeOfColor = false;
        for (auto neighbor : unassignedNeighbors) {
            const auto possibleNeighborColors = neighbor->getPossibleColors();
            const bool contains = possibleNeighborColors.find(color) != possibleNeighborColors.end();
            if (contains) {
                someNeighborCanBeOfColor = true;
                break;
            }
        }

        if (!someNeighborCanBeOfColor) {
            currentVertice->setFinalColor(color);
            verticesThatGainedColorsInCurrentIteration++;
            totalColoredVertices++;
            currentVertice->updateValue(static_cast<int>(color));
            removeAssignedColorFromNeighbors(currentVertice);
            break;
        }
    }
}

void SudokuGraph::tryToAssignColorByCheckingColumnExhaustion(Vertice *vertice, uint32_t &totalColoredVertices,
                                                             uint32_t &verticesThatGainedColorsInCurrentIteration) {
    auto columnNeighbors = vertice->getColumnNeighbors();
    auto unassignedColumnNeighbors = std::set<Vertice*>();
    for (auto columnNeighborIndex : columnNeighbors) {
        auto columnNeighbor = vertices[columnNeighborIndex];
        if (!columnNeighbor->isColored()) {
            unassignedColumnNeighbors.insert(columnNeighbor);
        }
    }
    assignColorToVerticeIfPossible(
            vertice, unassignedColumnNeighbors, totalColoredVertices, verticesThatGainedColorsInCurrentIteration);
}
