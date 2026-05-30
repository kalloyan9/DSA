
#pragma once
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>

namespace MyGraph
{
    template <typename T>
    class MyGraphAdjacencyList
    {
    public:
        explicit MyGraphAdjacencyList(size_t numVertices):
            adjacencyList(numVertices)
        {
        }

        void addEdge(const size_t src, const size_t dest)
        {
            if (src >= adjacencyList.size() || dest >= adjacencyList.size())
            {
                throw std::out_of_range("Vertex index out of range");
            }

            auto &srcList = adjacencyList[src];
            if (std::find(srcList.begin(), srcList.end(), static_cast<T>(dest)) == srcList.end())
            {
                srcList.push_back(static_cast<T>(dest));
            }

            // For undirected graph, add the reverse edge as well
            auto &destList = adjacencyList[dest];
            if (std::find(destList.begin(), destList.end(), static_cast<T>(src)) == destList.end())
            {
                destList.push_back(static_cast<T>(src));
            }
        }

        const std::vector<T> &getNeighbors(const size_t vertex) const
        {
            if (vertex >= adjacencyList.size())
            {
                throw std::out_of_range("Vertex index out of range");
            }
            return adjacencyList[vertex];
        }

        void print() const
        {
            for (size_t i = 0; i < adjacencyList.size(); ++i)
            {
                std::cout << "Vertex " << i << ": ";
                for (const auto &neighbor : adjacencyList[i])
                {
                    std::cout << neighbor << " ";
                }
                std::cout << std::endl;
            }
        }

    private:
        std::vector<std::vector<T>> adjacencyList;
    };
} // namespace MyGraph
