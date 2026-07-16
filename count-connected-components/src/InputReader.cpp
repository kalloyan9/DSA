#include "InputReader.h"

#include <cstdlib>

InputReader::InputReader(std::istream& is, std::ostream& os, std::ostream& err)
    : is_(is), os_(os), err_(err)
{
}

void InputReader::readDimensions(unsigned& rows, unsigned& cols) const
{
    os_ << "Enter the number of rows (n) and columns (m):" << std::endl;
    if (!(is_ >> rows >> cols)) {
        fail("Failed to read matrix dimensions.");
    }

    if (rows == 0u || cols == 0u) {
        fail("Invalid matrix dimensions. Rows and columns must be greater than zero.");
    }
}

void InputReader::readMatrix(ConnectedComponentsSolver& solver) const
{
    os_ << "Enter the matrix values (0 or 1) row by row:" << std::endl;

    for (unsigned i = 0u; i < solver.rows(); ++i) {
        for (unsigned j = 0u; j < solver.cols(); ++j) {
            int value;
            if (!(is_ >> value)) {
                fail("Failed to read matrix value.");
            }

            if (value != 0 && value != 1) {
                fail("Invalid matrix value. Please enter only 0 or 1.");
            }

            solver.setCell(i, j, value == 1);
        }
    }
}

void InputReader::fail(const std::string& message) const
{
    err_ << "[ERROR]: " << message << std::endl;
    std::exit(EXIT_FAILURE);
}
