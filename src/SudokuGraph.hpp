#ifndef ALG1_TP3_SUDOKUGRAPH_HPP
#define ALG1_TP3_SUDOKUGRAPH_HPP

#include <cstdint>
#include <list>
#include <vector>
#include <set>
#include "Vertice.hpp"

class SudokuGraph {
private:
    std::vector<std::set<uint32_t>> adjacencyLists;
    std::vector<Vertice*> vertices;
    uint32_t tableSize;
    uint32_t quadrantColumnWidth;
    uint32_t quadrantRowHeight;
    uint32_t amountOfColumns;
    uint32_t amountOfRows;
    void addEdgesToVerticesInSameColumn(uint32_t vertice);
    void addEdgesToVerticesInSameRow(uint32_t verticeIndex);
    void addEdgesToVerticesInSameQuadrant(uint32_t vertice);
public:
    SudokuGraph(uint32_t problemInstanceSize, uint32_t columns, uint32_t rows, const std::vector<Vertice*>& vertices);
    ~SudokuGraph();
    void addEdge(uint32_t from, uint32_t to);

    uint32_t getVerticeColumn(uint32_t verticeIndex) const;
    uint32_t getVerticeRow(uint32_t verticeIndex) const;
    void computeSaturation() const;
    void solve();

    void printAnswer(uint32_t totalColoredVertices) const;

    void removeAssignedColorFromPeers(Vertice *vertice);
    void tryToAssignColorByCheckingQuadrantExhaustion(uint32_t verticeIndex, uint32_t &totalColoredVertices,
                                                      uint32_t &verticesThatGainedColorsInCurrentIteration);

    void assignColorToSaturatedVertices(const std::vector<Vertice *> &copyVertices, uint32_t &totalColoredVertices,
                                        uint32_t &verticesThatGainedColorsInCurrentIteration);

    void assignColorToExhaustedUnit(uint32_t &totalColoredVertices,
                                    uint32_t &verticesThatGainedColorsInCurrentIteration);

    void tryToAssignColorByCheckingRowExhaustion(uint32_t verticeIndex, uint32_t &totalColoredVertices,
                                                 uint32_t &verticesThatGainedColorsInCurrentIteration);

    void tryToAssignColorByCheckingColumnExhaustion(uint32_t verticeIndex, uint32_t &totalColoredVertices,
                                                    uint32_t &verticesThatGainedColorsInCurrentIteration);

    void tryViaExhaustion(uint32_t &totalColoredVertices, uint32_t &verticesThatGainedColorsInCurrentIteration,
                          const std::set<Vertice *> &unassignedNeighbors, Vertice *currentVertice);
};

#endif
