#include <cassert>
#include <iostream>
#include "MyGraphAdjencyMatrix.hpp"

namespace MyGraph
{
    int MyGraphAdjacencyMatrixUTests()
    {
        MyGraphAdjacencyMatrix g(3);
        g.addEdge(0, 2);
        assert(g.hasEdge(0, 2));
        assert(g.hasEdge(2, 0));
        std::cout << "MyGraphAdjacencyMatrix tests passed.\n";
        return 0;
    }
} // namespace MyGraph
