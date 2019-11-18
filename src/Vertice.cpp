#include "Vertice.hpp"

Vertice::Vertice(const uint32_t index, const uint32_t row, const uint32_t column, const uint32_t value) : index(index),
    row(row),column(column), value(value), saturation(0) {
    this->possibleColors = std::set<Color>();
    if (value != 0) {
        possibleColors.insert(Color(value));
    } else {
        for (uint32_t i = 1; i < 10; i++) {
            possibleColors.insert(Color(i));
        }
    }
}

Vertice::~Vertice() = default;

bool Vertice::compareVerticesByDescendingSaturation(Vertice *a, Vertice *b) {
    return a->getSaturation() > b->getSaturation();
}

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

uint32_t Vertice::getSaturation() const {
    return this->saturation;
}

void Vertice::setSaturation(const uint32_t sat) {
    this->saturation = sat;
}

void Vertice::removeColorPossibility(Color color) {
    this->possibleColors.erase(color);
}
