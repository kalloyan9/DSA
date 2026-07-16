#pragma once

#include <iostream>
#include <istream>
#include <ostream>
#include <string>

#include "ConnectedComponentsSolver.h"

class InputReader {
public:
    InputReader(std::istream& is = std::cin,
                std::ostream& os = std::cout,
                std::ostream& err = std::cerr);

    void readDimensions(unsigned& rows, unsigned& cols) const;
    void readMatrix(ConnectedComponentsSolver& solver) const;

private:
    void fail(const std::string& message) const;

    std::istream& is_;
    std::ostream& os_;
    std::ostream& err_;
};
