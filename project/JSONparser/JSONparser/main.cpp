#include <vector>

#include "LogicHandler.hpp"
#include "Json.hpp"

// create objects:
static LogicHandler logicHandler{};
static Forest nodes; // forest of trees.

int main()
{
    // run cyclic
    while (kSUCCESS == logicHandler.runCyclic(nodes)) {

    }

    return 0;
}
