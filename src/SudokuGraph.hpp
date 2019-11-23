#ifndef ALG1_TP3_SUDOKUGRAPH_HPP
#define ALG1_TP3_SUDOKUGRAPH_HPP

#include <cstdint>
#include <list>
#include <vector>
#include <set>
#include "Vertice.hpp"

class SudokuGraph {
private:
    std::vector<Vertice*> vertices;
    const uint32_t quadrantColumnWidth;
    const uint32_t quadrantRowHeight;
    const uint32_t amountOfColumns;
    const uint32_t amountOfRows;

    void addEdgesToVerticesInSameColumn(Vertice *vertice);
    void addEdgesToVerticesInSameRow(Vertice *vertice);
    void addEdgesToVerticesInSameQuadrant(Vertice *vertice);
    uint32_t getVerticeColumn(uint32_t verticeIndex) const;
    uint32_t getVerticeRow(uint32_t verticeIndex) const;

    void printAnswer(uint32_t totalColoredVertices) const;

    void removeAssignedColorFromNeighbors(Vertice *vertice);


    void assignColorToSaturatedVertices(uint32_t &totalColoredVertices,
                                        uint32_t &verticesThatGainedColorsInCurrentIteration);

    void assignColorToExhaustedUnits(uint32_t &totalColoredVertices,
                                     uint32_t &verticesThatGainedColorsInCurrentIteration);

    void tryToAssignColorByCheckingRowExhaustion(Vertice *vertice, uint32_t &totalColoredVertices,
                                                 uint32_t &verticesThatGainedColorsInCurrentIteration);
    void tryToAssignColorByCheckingColumnExhaustion(Vertice *vertice, uint32_t &totalColoredVertices,
                                                    uint32_t &verticesThatGainedColorsInCurrentIteration);
    void tryToAssignColorByCheckingQuadrantExhaustion(Vertice *vertice, uint32_t &totalColoredVertices,
                                                    uint32_t &verticesThatGainedColorsInCurrentIteration);

    void assignColorToVerticeIfPossible(Vertice *currentVertice, const std::set<Vertice *> &unassignedNeighbors,
                                        uint32_t &totalColoredVertices,
                                        uint32_t &verticesThatGainedColorsInCurrentIteration);
public:
    SudokuGraph(uint32_t columns, uint32_t rows, const std::vector<Vertice *> &vertices);
    ~SudokuGraph();

    void solve();
};

#endif
