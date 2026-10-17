#pragma once

#include <cstddef>
#include <queue>
#include <set>
#include <stdexcept>
#include <vector>

#include "Globals.hpp"
#include "InputReader.hpp"

class Matrix
{
public:
    Matrix(std::size_t rows,
           std::size_t cols,
           std::size_t rowThreshold,
           std::size_t colThreshold,
           InputReader *reader);

    void setDimensions(const std::size_t rows, const std::size_t cols);
    std::size_t solve();

private:
    inline bool coords_validation(const globalTypes::CoordinatesType& coords) const
    {
        return (coords.row < _rows && coords.col < _cols &&
                (coords.row >= 0 && coords.col >=0));
    }

    globalTypes::Algo decideAlgo();
    bool insideMatrix(const globalTypes::CoordinatesType& coords) const;
    bool isVisited(std::size_t row, std::size_t col) const;
    std::size_t solveBFS();
    std::size_t solveLine();
    void bfs(std::size_t row, std::size_t col);

    std::size_t _rows;
    std::size_t _cols;
    std::size_t _rowThreshold;
    std::size_t _colThreshold;

    InputReader *_reader;
    globalTypes::Algo _algo;

    std::vector<globalTypes::LineType> _matrix;
    std::queue<globalTypes::CoordinatesType> _bfsQueue;
    std::vector<std::vector<bool>> _visited;

    globalTypes::LineType _curr_line;
    globalTypes::LineType _prev_line;
};
