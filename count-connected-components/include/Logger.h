#pragma once

#include <iosfwd>
#include <string>

// Interface for logging messages for complete abstraction and testability
class ILogger {
public:
    virtual ~ILogger() = default;
    virtual void logInfo(const std::string& message) = 0;
    virtual void logError(const std::string& message) = 0;
};

// Actual class implementation of ILogger that logs to console streams or files
class ConsoleLogger : public ILogger {
public:
    ConsoleLogger(std::ostream& out, std::ostream& err);
    void logInfo(const std::string& message) override;
    void logError(const std::string& message) override;

private:
    std::ostream& out_;
    std::ostream& err_;
};
