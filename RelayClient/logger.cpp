#include "logger.h"

#include <ctime>
#include <iomanip>

std::ofstream Logger::_logFile;
static Logger g_Logger;

Logger::Logger()
{
    _logFile.open(_filePath, std::ios::out | std::ios::app);
}

void Logger::writeMessage(const char *fileName, const char *functionName, int line, const char *message)
{
    std::time_t t = std::time(nullptr);
    _logFile << '[' << std::put_time(std::localtime(&t), "%c") << "]";
    _logFile << '#' << functionName << "()-" << line << '#';
    _logFile << message;
    _logFile << " (" << fileName << ')';
    _logFile << std::endl;
}

Logger::~Logger()
{
    _logFile.flush();
    _logFile.close();
}
