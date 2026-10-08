#pragma once

#include <types>
#include <queue>
#include <set>
#include <stdexcept>

class Matrix
{
public:
    // Constructor
    Matrix(std::size_t rows,
           std::size_t cols,
           std::size_t rowThreshold,
           std::size_t colThreshold,
           const InputReader *reader)
    
    // methods
    void setDimensions(const std::size_t rows, const std::size_t cols);
    std::size_t solve();

private:
    // helpers
    // returns true if coordinates are in range, false - otherwise
    inline bool coords_validation(globalTypes::CoordinatesType coords)
    {
        return ((coords.first >= 0ull && coords.second >= 0ull) &&
                (coords.first < _rows && coords.second < _cols));
    }
 
    inline bool isElementInSet(globalTypes::CoordinatesType element)
    {
        return (_coordsRemembered.find(element) != _coordsRemembered.end());
    }
 
    inline void removeFromSet(globalTypes::CoordinatesType element)
    {
        if (isElementInSet(element))
        {
            _coordsRemembered.erase(element);
        }
    }

    globalTypes::Algo decideAlgo();
    bool insideMatrix(globalTypes::CoordinatesType coords);
    std::size_t solveBFS();
    std::size_t solveLine();
    void bfs(std::size_t row, std::size_t col);

    // data members
    std::size_t _rows;
    std::size_t _cols;
    std::size_t _rowThreshold;
    std::size_t _colThreshold;

    const InputReader *_reader;
    globalTypes::Algo _algo;

    // used by the BFS algo
    std::vector<globalTypes::LineType> _matrix;
    std::queue<globalTypes::CoordinatesType> _bfsQueue;
    std::vector<std::vector<bool>> _visited;

    // data containers for line by line algo
    globalTypes::LineType _line; // container for big data - using the line algo
    std::set<globalTypes::CoordinatesType> _coordsRemembered; // container for the coordinates, used for line by line algo

};
