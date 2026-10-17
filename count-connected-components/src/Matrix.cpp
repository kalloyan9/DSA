#include "Matrix.hpp"

#include <iostream>
#include <queue>
#include <vector>

Matrix::Matrix(std::size_t rows,
               std::size_t cols,
               std::size_t rowThreshold,
               std::size_t colThreshold,
               InputReader *reader)
    : _rows(rows),
      _cols(cols),
      _rowThreshold(rowThreshold),
      _colThreshold(colThreshold),
      _reader(reader),
      _algo(globalTypes::UNDEF),
      _matrix(),
      _bfsQueue(),
      _visited(),
      _curr_line(),
      _prev_line()
{
}

void Matrix::setDimensions(const std::size_t rows, const std::size_t cols)
{
    _rows = rows;
    _cols = cols;
}

std::size_t Matrix::solve()
{
    // validate input
    if (!(_rows > 0 && _cols > 0))
    {
        return 0;
    }

    _algo = decideAlgo();

    switch (_algo)
    {
        case globalTypes::BFS:
            return solveBFS();

        case globalTypes::LINE:
            return solveLine();

        default:
            // should never enter here
            throw std::logic_error("Unknown algorithm.");
    }
}

globalTypes::Algo Matrix::decideAlgo()
{
    return (_rows <= _rowThreshold && _cols <= _colThreshold)
               ? globalTypes::BFS
               : globalTypes::LINE;
}

bool Matrix::insideMatrix(const globalTypes::CoordinatesType& coords) const
{
    return (coords.row < _rows && coords.col < _cols);
}

bool Matrix::isVisited(std::size_t row, std::size_t col) const
{
    return (row < _visited.size() && col < _visited[row].size() && _visited[row][col]);
}

void Matrix::bfs(std::size_t row, std::size_t col)
{
    std::queue<globalTypes::CoordinatesType> queue;
    queue.push(globalTypes::CoordinatesType(row, col));
    _visited[row][col] = true;

    while (!queue.empty())
    {
        const auto current = queue.front();
        queue.pop();

        const std::vector<globalTypes::CoordinatesType> neighbors = {
            globalTypes::CoordinatesType(current.row - 1, current.col),
            globalTypes::CoordinatesType(current.row + 1, current.col),
            globalTypes::CoordinatesType(current.row, current.col - 1),
            globalTypes::CoordinatesType(current.row, current.col + 1)
        };

        for (const auto& neighbor : neighbors)
        {
            if (!insideMatrix(neighbor))
                continue;

            if (_matrix[neighbor.row][neighbor.col] == 0)
                continue;

            if (_visited[neighbor.row][neighbor.col])
                continue;

            _visited[neighbor.row][neighbor.col] = true;
            queue.push(neighbor);
        }
    }
}

std::size_t Matrix::solveBFS()
{
    _matrix.clear();
    _matrix.reserve(_rows);
    for (std::size_t i = 0; i < _rows; ++i)
    {
        _matrix.emplace_back(_reader->readLine(_cols));
    }

    _visited.assign(_rows, std::vector<bool>(_cols, false));

    std::size_t connectedComponentsCount = 0;

    for (std::size_t row = 0; row < _rows; ++row)
    {
        for (std::size_t col = 0; col < _cols; ++col)
        {
            if (_matrix[row][col] != 0 && !isVisited(row, col))
            {
                ++connectedComponentsCount;
                bfs(row, col);
            }
        }
    }

    return connectedComponentsCount;
}

std::size_t Matrix::solveLine()
{
    std::size_t connectedComponentsCount = 0;
    for (std::size_t i = 0; i < _rows; ++i)
    {
        _curr_line.emplace_back(_reader->readLine(_cols));
        for (std::size_t j = 0; j < _curr_line.size(); ++j)
        {
            // if not null
            if (_curr_line[j] != 0)
            {
                // if same row prev col is valid and equals null or if prev row same col is valid and equals null
                if ((coords_validation({i, j - 1}) && 0 == _curr_line[j - 1]) ||
                    (coords_validation({i - 1, j}) && 0 == _prev_line[j]))
                {
                    ++connectedComponentsCount;
                }
            }
        }
        _prev_line = std::move(_curr_line);
    }

    return connectedComponentsCount;
}
