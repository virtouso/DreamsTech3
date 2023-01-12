#pragma once
#include <string>
#include <vector>

namespace Logging
{
    class LogEntry
    {
    };

    class Logger
    {
    public:
        static std::vector<LogEntry> messages;
        static void Log(const std::string& message);
        static void Err(const std::string& message);
    };
}
