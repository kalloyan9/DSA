#pragma once

#include <cstddef>
#include <cstdint>
#include <utility>
#include <vector>

class ConnectedComponentsSolver {
public:
    // type definitions for matrix storage
    using Matrix = std::vector<std::vector<std::uint8_t>>;

    // constructor owns matrix dimensions and validation semantics
    ConnectedComponentsSolver(std::size_t rows, std::size_t cols);

    // setters and getters
    void setCell(std::size_t row, std::size_t col, bool value);
    std::size_t rows() const noexcept;
    std::size_t cols() const noexcept;
    std::size_t countComponents();

private:
    // helper functions for traversal and state management
    void resetTraversalState() noexcept;
    void bfs(std::size_t startRow, std::size_t startCol, std::size_t currComponentCount);

    // data members for matrix dimensions, cell values, and visited state
    std::size_t rows_;
    std::size_t cols_;
    Matrix matrix_;
    Matrix visited_;
    using Cell = std::pair<std::size_t, std::size_t>; // type alias for cell coordinates
};
