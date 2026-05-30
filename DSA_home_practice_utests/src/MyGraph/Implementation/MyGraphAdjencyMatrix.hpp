#pragma once
#include <vector>
#include <stdexcept>
#include <iostream>

namespace MyGraph
{
    class MyGraphAdjacencyMatrix
    {
    public:
        MyGraphAdjacencyMatrix(size_t numVertices):
            adjacencyMatrix(numVertices, std::vector<bool>(numVertices, false))
        {
        }

        void addEdge(const size_t &src, const size_t &dest)
        {
            if (src >= adjacencyMatrix.size() || dest >= adjacencyMatrix.size())
            {
                throw std::out_of_range("Vertex index out of range");
            }

            adjacencyMatrix[src][dest] = true;
            adjacencyMatrix[dest][src] = true; // For undirected graph
        }

        bool hasEdge(const size_t &src, const size_t &dest) const
        {
            if (src >= adjacencyMatrix.size() || dest >= adjacencyMatrix.size())
            {
                throw std::out_of_range("Vertex index out of range");
            }

            return adjacencyMatrix[src][dest];
        }

        void print() const
        {
            for (size_t i = 0; i < adjacencyMatrix.size(); ++i)
            {
                std::cout << "Vertex " << i << ": ";
                for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j)
                {
                    if (adjacencyMatrix[i][j])
                    {
                        std::cout << j << " ";
                    }
                }
                std::cout << std::endl;
            }
        }

    // data members and other member functions can be added as needed
    private:
        std::vector<std::vector<bool>> adjacencyMatrix;
    };
} // namespace MyGraph
