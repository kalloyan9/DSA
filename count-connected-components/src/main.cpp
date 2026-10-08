#include <iostream>

#include "InputReader.hpp"
#include "Matrix.hpp"

int main()
{
    try
    {
        InputReader inputReader(std::cin);

        globalTypes::Coordinates dim =
            inputReader.readDimensions();

        Matrix matrix(dim.row,
                      dim.col,
                      inputReader,
                      5,
                      5);

        std::cout << matrix.solve() << std::endl;
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
