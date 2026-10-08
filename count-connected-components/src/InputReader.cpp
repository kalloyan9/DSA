#include "InputReader.hpp"
#include <stdexcept>

InputReader::InputReader(std::istream& input)
    : _input(input)
{}

globalTypes::Coordinates InputReader::readDimensions()
{
    std::size_t rows = 0;
    std::size_t cols = 0;

    if (!(_input >> rows >> cols))
        throw std::runtime_error("Cannot read matrix dimensions.");

    if (0 == rows || 0 == cols)
        throw std::runtime_error("Matrix dimensions must be positive.");

    return globalTypes::Coordinates(rows, cols);
}

globalTypes::LineType InputReader::readLine(std::size_t cols)
{
    globalTypes::LineType line;
    line.reserve(cols);

    std::size_t value;

    for (std::size_t i = 0; i < cols; ++i)
    {
        if (!(_input >> value))
            throw std::runtime_error("Cannot read matrix element.");

        if (value != 0 && value != 1)
            throw std::runtime_error("Matrix elements must be 0 or 1.");

        line.emplace_back(value);
    }

    return line;
}
