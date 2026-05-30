#include <cassert>
#include <iostream>
#include "MyGraphEdgeList.hpp"

namespace MyGraph
{
    int MyGraphEdgeListUTests()
    {
        {
            MyGraphEdgeList<size_t> g;
            g.addEdge(0, 1, 5);
            g.addEdge(1, 2, 3);
            const auto &edges = g.getEdges();
            assert(edges.size() == 2);
            assert(edges[0].src == 0);
            assert(edges[0].dest == 1);
            assert(edges[0].weight == 5);
        }

        std::cout << "MyGraphEdgeList tests passed.\n";
        return 0;
    }
} // namespace MyGraph
