#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>


class Logger
{
public:
    Logger();
    ~Logger();
    static void writeMessage(const char *fileName, const char *functionName, int line, const char *message);
private:
    const std::string _filePath = "log.log";
    static std::ofstream _logFile;
};

extern Logger g_Logger;
#define writeLog(message) g_Logger.writeMessage(__FILE__, __FUNCTION__, __LINE__, message)
#endif // LOGGER_H
