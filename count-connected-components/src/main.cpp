#include <cstdlib>
#include <exception>
#include <iostream>

#include "ConnectedComponentsSolver.h"
#include "InputReader.h"
#include "Logger.h"

int main()
{
    ConsoleLogger logger(std::cout, std::cerr);

    try {
        std::size_t rows = 0u;
        std::size_t cols = 0u;

        InputReader input(std::cin);

        logger.logInfo("Enter the number of rows (n) and columns (m):");
        input.readDimensions(rows, cols);

        ConnectedComponentsSolver solver(rows, cols);

        logger.logInfo("Enter the matrix values (0 or 1) row by row:");
        input.readMatrix(solver);

        const std::size_t numberOfConnectedComponents = solver.countComponents();
        logger.logInfo(std::to_string(numberOfConnectedComponents) + " figures");
        return EXIT_SUCCESS;
    } catch (const std::exception& error) {
        logger.logError(std::string("[ERROR]: ") + error.what());
        return EXIT_FAILURE;
    }
}
