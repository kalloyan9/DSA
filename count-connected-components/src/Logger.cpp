#include <ostream>
#include "Logger.h"

ConsoleLogger::ConsoleLogger(std::ostream& out, std::ostream& err)
    : out_(out), err_(err)
{
}

void ConsoleLogger::logInfo(const std::string& message)
{
    out_ << message << std::endl;
}

void ConsoleLogger::logError(const std::string& message)
{
    err_ << message << std::endl;
}
