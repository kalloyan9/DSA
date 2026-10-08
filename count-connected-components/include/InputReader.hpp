#pragma once

#include <cstddef>
#include <iostream>
#include <vector>

#include "Globals.hpp"

class InputReader
{
public:
    // constructor
    explicit InputReader(std::istream& input);
    // methods
    globalTypes::Coordinates readDimensions();
    globalTypes::LineType readLine(std::size_t cols);

private:
    // data members
    std::istream& _input;
};
