#include "Vertice.hpp"

Vertice::Vertice(const uint32_t index, const uint32_t row, const uint32_t column, const uint32_t value,
        const uint32_t instanceSize) : index(index), row(row), column(column), value(value) {
    this->adjacencyList = std::set<uint32_t>();
    this->rowNeighbors = std::set<uint32_t>();
    this->columnNeighbors = std::set<uint32_t>();
    this->quadrantNeighbors = std::set<uint32_t>();

    this->possibleColors = std::set<Color>();
    if (value != 0) {
        auto color = Color(value);
        possibleColors.insert(color);
        this->finalColor = color;
        this->colored = true;
    } else {
        for (uint32_t i = 1; i <= instanceSize; i++) {
            possibleColors.insert(Color(i));
        }
    }
}

Vertice::~Vertice() = default;

uint32_t Vertice::getRow() const {
    return row;
}

uint32_t Vertice::getColumn() const {
    return column;
}

uint32_t Vertice::getIndex() const {
    return index;
}

uint32_t Vertice::getValue() const {
    return value;
}

void Vertice::updateValue(const uint32_t newValue) {
    this->value = newValue;
}

void Vertice::setFinalColor(const Color color) {
    this->finalColor = color;
    this->colored = true;
}

void Vertice::removeColorPossibility(const Color color) {
    this->possibleColors.erase(color);
}

uint32_t Vertice::getAmountOfPossibleColors() {
    return this->possibleColors.size();
}

Color Vertice::getFinalColor() const {
    return this->finalColor;
}

std::set<Color> Vertice::getPossibleColors() {
    return this->possibleColors;
}

bool Vertice::isColored() const {
    return this->colored;
}

void Vertice::addEdge(const uint32_t to) {
    this->adjacencyList.insert(to);
}

std::set<uint32_t> Vertice::getAdjacencyList() const {
    return adjacencyList;
}

void Vertice::addRowNeighbor(const uint32_t neighborIndex) {
    this->rowNeighbors.insert(neighborIndex);
}

void Vertice::addColumnNeighbor(const uint32_t neighborIndex) {
    this->columnNeighbors.insert(neighborIndex);
}

void Vertice::addQuadrantNeighbor(const uint32_t neighborIndex) {
    this->quadrantNeighbors.insert(neighborIndex);
}

const std::set<uint32_t>& Vertice::getRowNeighbors() const {
    return rowNeighbors;
}

const std::set<uint32_t>& Vertice::getColumnNeighbors() const {
    return columnNeighbors;
}

const std::set<uint32_t>& Vertice::getQuadrantNeighbors() const {
    return quadrantNeighbors;
}
