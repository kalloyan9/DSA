#include "ConnectedComponentsSolver.h"

#include <queue>

ConnectedComponentsSolver::ConnectedComponentsSolver(unsigned rows, unsigned cols)
    : rows_(rows), cols_(cols), matrix_(rows, std::vector<bool>(cols, false)), visited_(rows, std::vector<bool>(cols, false))
{
}

void ConnectedComponentsSolver::setCell(unsigned row, unsigned col, bool value)
{
    if (row < rows_ && col < cols_) {
        matrix_[row][col] = value;
    }
}

unsigned ConnectedComponentsSolver::rows() const noexcept
{
    return rows_;
}

unsigned ConnectedComponentsSolver::cols() const noexcept
{
    return cols_;
}

unsigned ConnectedComponentsSolver::countComponents()
{
    unsigned componentCount = 0u;

    for (unsigned i = 0u; i < rows_; ++i) {
        for (unsigned j = 0u; j < cols_; ++j) {
            if (matrix_[i][j] && !visited_[i][j]) {
                if (bfs(i, j)) {
                    ++componentCount;
                }
            }
        }
    }

    return componentCount;
}

bool ConnectedComponentsSolver::bfs(unsigned startRow, unsigned startCol)
{
    bool foundComponent = false;
    std::queue<std::pair<unsigned, unsigned>> q;
    q.push({startRow, startCol});
    visited_[startRow][startCol] = true;

    while (!q.empty()) {
        auto [row, col] = q.front();
        q.pop();
        foundComponent = true;

        if (row > 0 && matrix_[row - 1][col] && !visited_[row - 1][col]) {
            visited_[row - 1][col] = true;
            q.push({row - 1, col});
        }
        if (row + 1 < rows_ && matrix_[row + 1][col] && !visited_[row + 1][col]) {
            visited_[row + 1][col] = true;
            q.push({row + 1, col});
        }
        if (col > 0 && matrix_[row][col - 1] && !visited_[row][col - 1]) {
            visited_[row][col - 1] = true;
            q.push({row, col - 1});
        }
        if (col + 1 < cols_ && matrix_[row][col + 1] && !visited_[row][col + 1]) {
            visited_[row][col + 1] = true;
            q.push({row, col + 1});
        }
    }

    return foundComponent;
}
