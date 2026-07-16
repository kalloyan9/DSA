#include "Logger.h"

#include <cassert>
#include <sstream>

void runLoggerTests()
{
    std::ostringstream out;
    std::ostringstream err;

    ConsoleLogger logger(out, err);

    logger.logInfo("info");
    logger.logError("error");

    assert(out.str() == "info\n");
    assert(err.str() == "error\n");
}