#include "LogicHandler.hpp"
#include "Json.hpp"

// create objects:
static LogicHandler logicHandler;

int main()
{
    // run cyclic
    while (kSUCCESS == logicHandler.runCyclic()) {

    }

    return 0;
}
