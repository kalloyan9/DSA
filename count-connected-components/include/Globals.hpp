#pragma once

#include <cstddef>
#include <iostream>
#include <vector>

namespace globalTypes
{
    using SizeType = std::size_t;

    struct Coordinates
    {
        SizeType row;
        SizeType col;

        Coordinates() : row(0), col(0) {}

        Coordinates(SizeType r, SizeType c)
            : row(r), col(c)
        {
        }

        bool operator<(const Coordinates& other) const
        {
            if (row != other.row)
                return row < other.row;

            return col < other.col;
        }
    };

    inline std::ostream& operator<<(std::ostream& os,
                                    const Coordinates& coords)
    {
        os << "(" << coords.row << ", " << coords.col << ")";
        return os;
    }

    using LineType = std::vector<std::size_t>;

    enum Algo
    {
        UNDEF = 0,
        BFS,
        LINE
    };
}
