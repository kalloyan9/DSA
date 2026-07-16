#include <iostream>

extern void runLoggerTests();

int main()
{
    try {
        runLoggerTests();
        std::cout << "All logger tests passed.\n";
        return 0;
    } catch (...) {
        std::cerr << "Logger tests failed.\n";
        return 1;
    }
}
