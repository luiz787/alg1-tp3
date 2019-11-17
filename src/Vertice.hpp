#ifndef ALG1_TP3_VERTICE_HPP
#define ALG1_TP3_VERTICE_HPP


#include <cstdint>

class Vertice {
private:
    uint32_t index;
    uint32_t row;
    uint32_t column;
    uint32_t value;
public:
    Vertice(uint32_t index, uint32_t row, uint32_t column, uint32_t value);
    ~Vertice();
    uint32_t getRow() const;
    uint32_t getColumn() const;
    uint32_t getValue() const;
    uint32_t getLinearIndex() const;

    void updateValue(uint32_t newValue);
};


#endif