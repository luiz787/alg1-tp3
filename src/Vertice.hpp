#ifndef ALG1_TP3_VERTICE_HPP
#define ALG1_TP3_VERTICE_HPP

#include <cstdint>
#include <set>
#include "Color.hpp"

class Vertice {
private:
    const uint32_t index;
    const uint32_t row;
    const uint32_t column;
    std::set<Color> possibleColors;
    Color finalColor;
    bool colored;
    std::set<uint32_t> adjacencyList;
    std::set<uint32_t> rowNeighbors;
    std::set<uint32_t> columnNeighbors;
    std::set<uint32_t> quadrantNeighbors;

    uint32_t value;
public:
    Vertice(uint32_t index, uint32_t row, uint32_t column, uint32_t value, uint32_t instanceSize);
    ~Vertice();

    uint32_t getRow() const;
    uint32_t getColumn() const;
    uint32_t getValue() const;
    std::set<uint32_t> getAdjacencyList() const;

    uint32_t getIndex() const;
    bool isColored() const;
    Color getFinalColor() const;

    void setFinalColor(Color color);
    uint32_t getQuantityOfPossibleColors();
    std::set<Color> getPossibleColors();

    void updateValue(uint32_t newValue);
    void removeColorPossibility(Color color);

    void addEdge(uint32_t to);
    void addRowNeighbor(uint32_t neighborIndex);
    void addColumnNeighbor(uint32_t neighborIndex);
    void addQuadrantNeighbor(uint32_t neighborIndex);

    const std::set<uint32_t>& getRowNeighbors() const;
    const std::set<uint32_t>& getColumnNeighbors() const;
    const std::set<uint32_t>& getQuadrantNeighbors() const;
};


#endif