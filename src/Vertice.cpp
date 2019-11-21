#include "Vertice.hpp"

Vertice::Vertice(const uint32_t index, const uint32_t row, const uint32_t column, const uint32_t value, const uint32_t instanceSize) : index(index),
    row(row),column(column), value(value), saturation(0) {
    this->possibleColors = std::set<Color>();
    if (value != 0) {
        possibleColors.insert(Color(value));
        this->finalColor = Color(value);
        this->isColored = true;
    } else {
        for (uint32_t i = 1; i <= instanceSize; i++) {
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

void Vertice::setFinalColor(const Color color) {
    this->finalColor = color;
    this->isColored = true;
}

void Vertice::removeColorPossibility(const Color color) {
    this->possibleColors.erase(color);
}

uint32_t Vertice::getQuantityOfPossibleColors() {
    return this->possibleColors.size();
}

Color Vertice::getFinalColor() const {
    return this->finalColor;
}

std::set<Color> Vertice::getPossibleColors() {
    return this->possibleColors;
}

bool Vertice::getIsColored() const {
    return this->isColored;
}
