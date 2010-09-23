#include "Logging.h"

namespace Logger
{

void log(const char* timestamp, const char* file, const char* function, int line, ...)
{
    char fullMsg[1024];
    VA_ARGS_TO_CHAR(line, fullMsg);

    std::clog << timestamp << " - " << file << " - " <<
            function << " - " << line << " - " <<
            fullMsg << std::endl;
}

void error(const char* timestamp, const char* file, const char* function, int line, ...)
{
    char fullMsg[1024];
    VA_ARGS_TO_CHAR(line, fullMsg);

    std::clog << "#" << "ERROR" << "#: " << timestamp << " - " <<
            file << " - " << function << " - " << line << " - " <<
            fullMsg << std::endl;
}

};
