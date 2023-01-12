#pragma once
#include <string>
#include <vector>

namespace Logging
{

    enum LogType
    {
        Info,
        Warning,
        Error
    };
    struct LogEntry
    {
        LogType Type;
        std::string Message;
    };

    class Logger
    {
    public:
        static std::vector<LogEntry> _messages;
        static void Log(const std::string& message);
        static void Err(const std::string& message);
    };
}
