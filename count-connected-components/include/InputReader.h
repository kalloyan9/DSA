#pragma once

#include <cstddef>
#include <istream>
#include <stdexcept>
#include <string>

class ConnectedComponentsSolver;

class InputError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class InputReader {
public:
    explicit InputReader(std::istream& is);

    void readDimensions(std::size_t& rows, std::size_t& cols) const;
    void readMatrix(ConnectedComponentsSolver& solver) const;

private:
    void fail(const std::string& message) const;

    std::istream& is_;
};
