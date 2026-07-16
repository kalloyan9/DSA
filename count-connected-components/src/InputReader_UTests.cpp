#include "InputReader.h"
#include "ConnectedComponentsSolver.h"

#include <cassert>
#include <iostream>
#include <sstream>

void runInputReaderTests()
{
    // Test 1: Valid dimensions
    {
        std::cout << "InputReader Test 1: valid dimensions...\n";

        std::istringstream input("2 3");
        InputReader reader(input);

        std::size_t rows = 0;
        std::size_t cols = 0;
        reader.readDimensions(rows, cols);

        assert(rows == 2);
        assert(cols == 3);
    }

    // Test 2: Invalid dimensions (zero)
    {
        std::cout << "InputReader Test 2: invalid zero dimensions...\n";

        std::istringstream input("0 1");
        InputReader reader(input);

        bool threw = false;

        try {
            std::size_t rows = 0;
            std::size_t cols = 0;
            reader.readDimensions(rows, cols);
        } catch (const InputError&) {
            threw = true;
        }

        assert(threw);
    }

    // Test 3: Invalid dimensions (non-numeric)
    {
        std::cout << "InputReader Test 3: invalid non-numeric dimensions...\n";

        std::istringstream input("a b");
        InputReader reader(input);

        bool threw = false;

        try {
            std::size_t rows = 0;
            std::size_t cols = 0;
            reader.readDimensions(rows, cols);
        } catch (const InputError&) {
            threw = true;
        }

        assert(threw);
    }

    // Test 4: Valid matrix input
    {
        std::cout << "InputReader Test 4: valid matrix input...\n";

        std::istringstream input("1 0");
        InputReader reader(input);

        ConnectedComponentsSolver solver(1, 2);
        reader.readMatrix(solver);

        const std::size_t componentCount = solver.countComponents();
        assert(1u == componentCount);
    }

    // Test 5: Invalid matrix input
    {
        std::cout << "InputReader Test 5: invalid matrix value...\n";

        std::istringstream input("2");
        InputReader reader(input);

        ConnectedComponentsSolver solver(1, 1);
        bool threw = false;

        try {
            reader.readMatrix(solver);
        } catch (const InputError&) {
            threw = true;
        }

        assert(threw);
    }

    std::cout << "InputReader module tests passed.\n";
}