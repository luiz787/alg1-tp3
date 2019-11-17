#include "Vertice.hpp"

Vertice::Vertice(uint32_t index, uint32_t row, uint32_t column, uint32_t value) : index(index), row(row),
                                                                                  column(column), value(value) {}

Vertice::~Vertice() = default;

uint32_t Vertice::getRow() const {
    return row;
}

uint32_t Vertice::getColumn() const {
    return column;
}

uint32_t Vertice::getValue() const {
    return value;
}

void Vertice::updateValue(uint32_t newValue) {
    this->value = newValue;
}

uint32_t Vertice::getLinearIndex() const {
    return;
}
