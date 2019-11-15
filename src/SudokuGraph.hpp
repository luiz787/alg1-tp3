#ifndef ALG1_TP3_SUDOKUGRAPH_HPP
#define ALG1_TP3_SUDOKUGRAPH_HPP

#include <cstdint>
#include <list>
#include <vector>

class SudokuGraph {
private:
    std::vector<std::list<uint16_t>> adjacencyLists;
    uint32_t columns;
    uint32_t rows;
    void addEdgesToVerticesInSameColumn(uint32_t vertice);
    void addEdgesToVerticesInSameRow(uint32_t vertice);
    void addEdgesToVerticesInSameQuadrant(uint32_t vertice);
public:
    SudokuGraph(uint16_t columns, uint16_t rows);
    ~SudokuGraph();
    uint32_t getColumns();
    uint32_t getRows();
    void addEdge(uint16_t from, uint16_t to);
};

#endif
