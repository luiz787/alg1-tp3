#ifndef ALG1_TP3_VERTICE_HPP
#define ALG1_TP3_VERTICE_HPP

#include <cstdint>
#include <set>
#include "Color.hpp"

class Vertice {
private:
    const uint32_t index;
    std::set<Color> possibleColors;
    Color color;
    std::set<uint32_t> adjacencyList;
    std::set<uint32_t> rowNeighbors;
    std::set<uint32_t> columnNeighbors;
    std::set<uint32_t> quadrantNeighbors;

    uint32_t value;
public:
    Vertice(uint32_t index, uint32_t value, uint32_t instanceSize);
    ~Vertice();

    std::set<uint32_t> getAdjacencyList() const;

    uint32_t getIndex() const;
    bool isColored() const;
    Color getColor() const;

    void setFinalColor(Color color);
    uint32_t getAmountOfPossibleColors();
    std::set<Color> getPossibleColors();

    void updateValue(uint32_t newValue);
    void removeColorPossibility(Color color);

    void addNeighbor(uint32_t neighbor);
    void addRowNeighbor(uint32_t neighborIndex);
    void addColumnNeighbor(uint32_t neighborIndex);
    void addQuadrantNeighbor(uint32_t neighborIndex);

    const std::set<uint32_t>& getRowNeighbors() const;
    const std::set<uint32_t>& getColumnNeighbors() const;
    const std::set<uint32_t>& getQuadrantNeighbors() const;
};


#endif