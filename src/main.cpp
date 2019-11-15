#include <iostream>
#include <fstream>
#include "SudokuGraph.hpp"

std::ifstream openInputFile(int argc, char** argv);

int main(int argc, char**argv) {
    std::cout << "Hello, world!";
    auto inputFile = openInputFile(argc, argv);
    uint32_t tableSize;
    uint32_t columns;
    uint32_t rows;
    inputFile >> tableSize >> columns >> rows;
    SudokuGraph graph = SudokuGraph(columns, rows);
    for (uint32_t i = 0; i < columns; i++) {
        for (uint32_t j = 0; j < rows; i++) {
            uint32_t value;
            inputFile >> value;
        }
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