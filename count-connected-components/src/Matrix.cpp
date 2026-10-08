#include "Matrix.hpp"

Matrix::Matrix(std::size_t rows,
               std::size_t cols,
               std::size_t rowThreshold = 1'000'000,
               std::size_t colThreshold = 1'000'000)
               const InputReader *reader,
    :
    _rows(rows),
    _cols(cols),
    _rowThreshold(rowThreshold),
    _colThreshold(colThreshold),
    _reader(reader),
    _algo(globalTypes::UNDEF),
    _matrix(),
    _visited(),
    _line(),
    _bfsQueue(),
    _coordsRemembered()
{
}

void Matrix::setDimensions(const std::size_t rows, const std::size_t cols)
{
    _rows = rows;
    _cols = cols;
}

std::size_t Matrix::solve()
{
    _algo = decideAlgo();
    std::cout << "[LOG] Deciding algorithm..." << _algo << std::endl;

    switch (_algo)
    {
        case globalTypes::BFS:
            return solveBFS();

        case globalTypes::LINE:
            return solveLine();

        default:
            throw std::logic_error("Unknown algorithm.");
    }
}

globalTypes::Algo Matrix::decideAlgo()
{
    return (_rows <= _rowThreshold && _cols <= _colThreshold) ? 
            globalTypes::BFS :
            globalTypes::LINE;
}

bool Matrix::insideMatrix(globalTypes::CoordinatesType coords)
{
    return ((coords.first >= 0ull && coords.second >= 0ull) &&
            (coords.first < _rows && coords.second < _cols));
}

std::size_t Matrix::solveBFS()
{
    // read the matrix
    _matrix.reserve(_rows);
    for (std::size_t i = 0; i < _rows; ++i)
    {
        _matrix.emplace_back(_reader->readLine(_cols));
    }

    // initialize the visited matrix
    _visited.resize(_rows, std::vector<bool>(_cols, false));

    std::size_t connectedComponentsCount = 0;

    for (std::size_t row = 0; row < _rows; ++row)
    {
        for (std::size_t col = 0; col < _cols; ++col)
        {
            if (0 != _matrix[row][col] && false == isVisited(row, col))
            {
                ++connectedComponentsCount;

                _bfsQeue.push(globalTypes::Coordinates(row, col));
                _visited[row][col] = true;
                while (!_bfsQueue.empty())
                {
                    globalTypes::Coordinates current = _bfsQueue.front();
                    _bfsQueue.pop();

                    std::size_t currentRow = current.row;
                    std::size_t currentCol = current.col;

                    // check all 4 neighbors
                    const std::vector<globalTypes::Coordinates> neighbors = {
                        {currentRow - 1, currentCol}, // up
                        {currentRow + 1, currentCol}, // down
                        {currentRow, currentCol - 1}, // left
                        {currentRow, currentCol + 1}  // right
                    };

                    for (const auto& neighbor : neighbors)
                    {
                        if (insideMatrix(neighbor) &&
                            false == _visited[neighbor.row][neighbor.col] &&
                            0 != _matrix[neighbor.row][neighbor.col])
                        {
                            _bfsQueue.push(neighbor);
                            _visited[neighbor.row][neighbor.col] = true;
                        }
                    }
                }
            }
        }
    }

    return connectedComponentsCount;
}

std::size_t Matrix::solveLine()
{
    std::size_t connectedComponentsCount = 0;

    for (size_t i = 0; i < _rows; ++i)
    {
        _line = _reader->readLine(_cols);
        for (size_t j = 0; j < _cols; ++j)
        {
            static globalTypes::CoordinatesType current = {i, j};
            static globalTypes::CoordinatesType previousRow = {i - 1, j};
            static globalTypes::CoordinatesType previousCol = {i, j - 1};

            // validity check
            if (false == insideMatrix(current))
                throw std::logic_error("Current coordinates are out of bounds.");
            
            // if element is not null, add it to the set
            if (0 != _line[j])
            {
                if (!isElementInSet(current))
                {
                    ++connectedComponentsCount;
                    _coordsRemembered.insert(current);
                }
            }
            else
            {
                // figure ended, remove from the set
                if (insideMatrix(previousRow))
                {
                    removeFromSet(previousRow);
                }
                if (insideMatrix(previousCol))
                {
                    removeFromSet(previousCol);
                }
            }
        }
    }

    return connectedComponentsCount;
}
