#ifndef _LOGGING_H_
#define _LOGGING_H_

#include <stdio.h>
#include <stdarg.h>

#define VA_ARGS_TO_CHAR(variable, buffer) va_list args; \
                                          va_start(args, variable); \
                                          char* msg = va_arg(args, char *);\
                                          vsprintf(buffer, msg, args);

namespace Logger
{
    void log(const char* timestamp, const char* file, const char* function, int line, ...);
    void error(const char* timestamp, const char* file, const char* function, int line, ...);
}

#define LOG_ERROR(...) Logger::error(__TIMESTAMP__, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)

#ifdef _DEBUG
#define DEBUG
#endif
#ifdef DEBUG
#define LOG(...) Logger::log(__TIMESTAMP__, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#else
#define LOG(...)
#endif

#endif //_LOGGING_H_
