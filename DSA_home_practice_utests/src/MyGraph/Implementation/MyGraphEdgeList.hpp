#pragma once
#include <vector>
#include <iostream>

namespace MyGraph
{
    template <typename T>
    struct Edge
    {
        T src; // Source vertex
        T dest; // Destination vertex
        size_t weight; // Optional weight for weighted graphs

        Edge(const T &source, const T &destination, const size_t &w = 0) :
            src(source),
            dest(destination),
            weight(w)
        {
        }
    };

    template <typename T>
    class MyGraphEdgeList
    {
    public:
        MyGraphEdgeList() = default;

        void addEdge(const T &src, const T &dest, const size_t &weight = 0)
        {
            edgeList.emplace_back(src, dest, weight);
        }

        const std::vector<Edge<T>> &getEdges() const
        {
            return edgeList;
        }

        void print() const
        {
            for (const auto &edge : edgeList)
            {
                std::cout << "Edge from " << edge.src << " to " << edge.dest
                          << " with weight " << edge.weight << std::endl;
            }
        }

    private:
        std::vector<Edge<T>> edgeList; // List of edges
    };
}
