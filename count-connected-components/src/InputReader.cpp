#include <limits>
#include "ConnectedComponentsSolver.h"
#include "InputReader.h"

InputReader::InputReader(std::istream& is)
    : is_(is)
{
}

void InputReader::readDimensions(std::size_t& rows, std::size_t& cols) const
{
    unsigned long long rawRows = 0;
    unsigned long long rawCols = 0;

    if (!(is_ >> rawRows >> rawCols)) {
        fail("Failed to read matrix dimensions.");
    }

    if (0u == rawRows || 0u == rawCols) {
        fail("Invalid matrix dimensions. Rows and columns must be greater than zero.");
    }

    const std::size_t maxSize = std::numeric_limits<std::size_t>::max();
    if (rawRows > maxSize || rawCols > maxSize) {
        fail("Matrix dimensions exceed supported maximum.");
    }

    rows = static_cast<std::size_t>(rawRows);
    cols = static_cast<std::size_t>(rawCols);
}

void InputReader::readMatrix(ConnectedComponentsSolver& solver) const
{
    for (std::size_t i = 0u; i < solver.rows(); ++i) {
        for (std::size_t j = 0u; j < solver.cols(); ++j) {
            int value = 0;
            if (!(is_ >> value)) {
                fail("Failed to read matrix value.");
            }

            if (0 != value && 1 != value) {
                fail("Invalid matrix value. Please enter only 0 or 1.");
            }

            solver.setCell(i, j, value == 1);
        }
    }
}

void InputReader::fail(const std::string& message) const
{
    throw InputError(message);
}
