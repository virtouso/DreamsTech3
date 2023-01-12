#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

#include "Logger.h"
#include <chrono>

#include <ctime>
#include <iostream>
#include <ostream>
#include <vector>


std::vector<Logging::LogEntry> Logging::Logger:: _messages;
std::string GetCurrentDateTime()
{
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string output(30, '\0');
    std::strftime(&output[0], output.size(), "%d-%b-%Y %H:%M:%S", std::localtime(&now));

    return output;
}


void Logging::Logger::Log(const std::string& message)
{

    LogEntry log;
    log.Type= Info;
    log.Message= message + ":" + GetCurrentDateTime();
    std::cout << log.Message << std::endl;

    _messages.push_back(log);
}

void Logging::Logger::Err(const std::string& message)
{
    LogEntry log;
    log.Type= Info;
    log.Message= "\033[32m" + message + ":" + GetCurrentDateTime() + "\033[0m";
    std::cout << log.Message << std::endl;
    _messages.push_back(log);
}
