#ifndef ALG1_TP3_SUDOKUGRAPH_HPP
#define ALG1_TP3_SUDOKUGRAPH_HPP

#include <cstdint>
#include <vector>
#include <set>

class SudokuGraph {
private:
    std::vector<std::set<uint32_t>> adjacencyLists;
    uint32_t tableSize;
    uint32_t quadrantColumnWidth;
    uint32_t quadrantRowHeight;
    uint32_t amountOfColumns;
    uint32_t amountOfRows;
    void addEdgesToVerticesInSameColumn(uint32_t vertice);
    void addEdgesToVerticesInSameRow(uint32_t verticeIndex);
    void addEdgesToVerticesInSameQuadrant(uint32_t vertice);
public:
    SudokuGraph(uint32_t tableSize, uint32_t columns, uint32_t rows);
    ~SudokuGraph();
    uint32_t getColumns();
    uint32_t getRows();
    void addEdge(uint32_t from, uint32_t to);

    uint32_t getVerticeColumn(uint32_t verticeIndex) const;
    uint32_t getVerticeRow(uint32_t verticeIndex) const;
};

#endif
