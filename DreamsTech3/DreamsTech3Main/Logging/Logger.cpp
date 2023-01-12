#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

#include "Logger.h"
#include <chrono>

#include <ctime>
#include <iostream>
#include <ostream>
#include <vector>

//std::vector<LogEntry>

std::string GetCurrentDateTime()
{
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string output(30, '\0');
    std::strftime(&output[0], output.size(), "%d-%b-%Y %H:%M:%S", std::localtime(&now));

    return output;
}


void Logging::Logger::Log(const std::string& message)
{
    std::cout << message << ":" << GetCurrentDateTime() << std::endl;
}

void Logging::Logger::Err(const std::string& message)
{
    std::cout << "\033[32m" << message << ":" << GetCurrentDateTime() << "\033[0m" << std::endl;
}
