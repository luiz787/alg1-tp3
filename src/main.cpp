#include <iostream>
#include <fstream>
#include "SudokuGraph.hpp"
#include "Vertice.hpp"

std::ifstream openInputFile(int argc, char** argv);

int main(int argc, char**argv) {
    auto inputFile = openInputFile(argc, argv);
    uint32_t tableSize;
    uint32_t columns;
    uint32_t rows;
    inputFile >> tableSize >> columns >> rows;
    auto vertices = std::vector<Vertice*>();
    const uint32_t squareSize = columns * rows;
    for (uint32_t i = 0; i < squareSize; i++) {
        for (uint32_t j = 0; j < squareSize; j++) {
            uint32_t value;
            inputFile >> value;
            const uint32_t verticeIndex = i * squareSize + j;
            const auto vertice = new Vertice(verticeIndex, value, tableSize);
            vertices.push_back(vertice);
        }
    }
    SudokuGraph graph = SudokuGraph(columns, rows, vertices);
    graph.solve();

    for (auto vertice : vertices) {
        delete(vertice);
    }
    return 0;
}

std::ifstream openInputFile(int argc, char** argv) {
    if (argc < 2) {
        throw std::invalid_argument("Nome do arquivo de entrada deve ser passado como argumento.");
    }
    const char* inputFileName = argv[1];
    std::ifstream inputFile (inputFileName);
    if (!inputFile.is_open()) {
        throw std::invalid_argument("Falha ao abrir o arquivo de entrada.");
    }
    return inputFile;
}