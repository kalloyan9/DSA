#include <iostream>

#include "ConnectedComponentsSolver.h"
#include "InputReader.h"

int main()
{
    unsigned rows = 0u;
    unsigned cols = 0u;

    InputReader input(std::cin, std::cout, std::cerr);
    input.readDimensions(rows, cols);

    ConnectedComponentsSolver solver(rows, cols);
    input.readMatrix(solver);

    const unsigned numberOfConnectedComponents = solver.countComponents();
    std::cout << "Total number of connected components: " << numberOfConnectedComponents << std::endl;

    return 0;
}
