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

    uint32_t value;
    uint32_t saturation;
public:
    Vertice(uint32_t index, uint32_t row, uint32_t column, uint32_t value, uint32_t instanceSize);
    ~Vertice();

    static bool compareVerticesByDescendingSaturation(Vertice* a, Vertice* b);
    uint32_t getRow() const;
    uint32_t getColumn() const;
    uint32_t getValue() const;
    uint32_t getSaturation() const;
    uint32_t getIndex() const;
    Color getFinalColor() const;
    void setSaturation(uint32_t saturation);
    void setFinalColor(Color color);
    uint32_t getQuantityOfPossibleColors();
    std::set<Color> getPossibleColors();

    void updateValue(uint32_t newValue);
    void removeColorPossibility(Color color);
};


#endif