#include <iostream>

extern void runSolverTests();

int main()
{
    try {
        runSolverTests();
        std::cout << "All solver tests passed.\n";
        return 0;
    } catch (...) {
        std::cerr << "Solver tests failed.\n";
        return 1;
    }
}
