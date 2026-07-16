#include <iostream>

extern void runSolverTests();
extern void runInputReaderTests();
extern void runLoggerTests();

int main()
{
    try {
        std::cout << "Running all unit tests...\n\n";
        runSolverTests();
        runInputReaderTests();
        runLoggerTests();
        std::cout << "All unit tests passed.\n";
        return 0;
    } catch (...) {
        std::cerr << "Unit tests failed.\n";
        return 1;
    }
}
