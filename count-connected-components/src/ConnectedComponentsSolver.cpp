#include <queue>
#include <stdexcept>

#include "ConnectedComponentsSolver.h"


ConnectedComponentsSolver::ConnectedComponentsSolver(std::size_t rows, std::size_t cols)
    : rows_(rows), cols_(cols), matrix_(rows, std::vector<std::uint8_t>(cols, 0u)), visited_(rows, std::vector<std::uint8_t>(cols, 0u))
{
    if (0u == rows || 0u == cols) {
        throw std::invalid_argument("ConnectedComponentsSolver requires rows and cols greater than zero.");
    }
}

void ConnectedComponentsSolver::setCell(std::size_t row, std::size_t col, bool value)
{
    if (row >= rows_ || col >= cols_) {
        throw std::out_of_range("Cell coordinate is out of range.");
    }
    matrix_[row][col] = static_cast<std::uint8_t>(value ? 1u : 0u);
}

std::size_t ConnectedComponentsSolver::rows() const noexcept
{
    return rows_;
}

std::size_t ConnectedComponentsSolver::cols() const noexcept
{
    return cols_;
}

void ConnectedComponentsSolver::resetTraversalState() noexcept
{
    for (std::size_t i = 0u; i < rows_; ++i) {
        for (std::size_t j = 0u; j < cols_; ++j) {
            visited_[i][j] = 0u;
        }
    }
}

std::size_t ConnectedComponentsSolver::countComponents()
{
    resetTraversalState();

    std::size_t componentCount = 0u;
    for (std::size_t i = 0u; i < rows_; ++i) {
        for (std::size_t j = 0u; j < cols_; ++j) {
            if (0u != matrix_[i][j] && 0u == visited_[i][j]) {
                ++componentCount;
                bfs(i, j);
            }
        }
    }

    return componentCount;
}

void ConnectedComponentsSolver::bfs(std::size_t startRow, std::size_t startCol)
{
    static constexpr int kRowOffsets[] = { -1, 1, 0, 0 };
    static constexpr int kColOffsets[] = { 0, 0, -1, 1 };

    std::queue<Cell> q;
    q.emplace(startRow, startCol);
    visited_[startRow][startCol] = 1u;

    while (!q.empty()) {
        const Cell cell = q.front();
        q.pop();

        const unsigned long long currentRow = cell.first;
        const unsigned long long currentCol = cell.second;

        for (std::size_t index = 0; index < 4; ++index) {
            unsigned long long nextRow = currentRow;
            unsigned long long nextCol = currentCol;

            if (kRowOffsets[index] < 0) {
                if (currentRow == 0ull) {
                    continue;
                }
                nextRow = currentRow - 1ull;
            } else if (kRowOffsets[index] > 0) {
                nextRow = currentRow + 1ull;
            }

            if (kColOffsets[index] < 0) {
                if (currentCol == 0ull) {
                    continue;
                }
                nextCol = currentCol - 1ull;
            } else if (kColOffsets[index] > 0) {
                nextCol = currentCol + 1ull;
            }

            if (nextRow >= rows_ || nextCol >= cols_) {
                continue;
            }

            const std::size_t nextRowIndex = static_cast<std::size_t>(nextRow);
            const std::size_t nextColIndex = static_cast<std::size_t>(nextCol);

            if (0u != matrix_[nextRowIndex][nextColIndex] &&
                0u == visited_[nextRowIndex][nextColIndex]) {
                visited_[nextRowIndex][nextColIndex] = 1u;
                q.emplace(nextRowIndex, nextColIndex);
            }
        }
    }
}
