#include <iostream>

extern void runInputReaderTests();

int main()
{
    try {
        runInputReaderTests();
        std::cout << "All input reader tests passed.\n";
        return 0;
    } catch (...) {
        std::cerr << "Input reader tests failed.\n";
        return 1;
    }
}
