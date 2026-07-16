#pragma once

#include <vector>

class ConnectedComponentsSolver {
public:
    using Matrix = std::vector<std::vector<bool>>;
    using ComponentMatrix = std::vector<std::vector<unsigned>>;

    ConnectedComponentsSolver(unsigned rows, unsigned cols);

    void setCell(unsigned row, unsigned col, bool value);
    unsigned rows() const noexcept;
    unsigned cols() const noexcept;
    unsigned countComponents();
    unsigned getComponentId(unsigned row, unsigned col) const noexcept;
    const ComponentMatrix& getComponentMatrix() const noexcept;

private:
    bool bfs(unsigned startRow, unsigned startCol, unsigned componentId);

    unsigned rows_;
    unsigned cols_;
    Matrix matrix_;
    Matrix visited_;
    ComponentMatrix componentIds_;
};
