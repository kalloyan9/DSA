#include <cassert>
#include <iostream>
#include "MyGraphAdjacencyList.hpp"

namespace MyGraph
{
    int MyGraphAdjacencyListUTests()
    {
        {
            // create graph with 3 vertices
            MyGraphAdjacencyList<size_t> g(3);
            g.addEdge(0, 1);
            g.addEdge(1, 2);
            const auto &n0 = g.getNeighbors(0);
            assert(n0.size() == 1);
            assert(n0[0] == 1);
            const auto &n1 = g.getNeighbors(1);
            // neighbors should contain 0 and 2 (undirected)
            assert(n1.size() == 2);
        }

        std::cout << "MyGraphAdjacencyList tests passed.\n";
        return 0;
    }
} // namespace MyGraph
