#ifndef _LOGGING_H_
#define _LOGGING_H_

#include <stdarg.h>
#include <iostream>

namespace Logger
{
    //static keyword is required so no multiple compile
    //instances would be created  by the compiler
    static void log(const char* timestamp, const char* file, const char* function, int line, ...)
    {
        va_list args;
        va_start(args, line);

        char* msg = va_arg(args, char *);

        char fullmsg[512];

        vsprintf(fullmsg, msg, args);

        std::clog << timestamp << " --- " << file << " --- " << function << " --- " << line << " --- " << fullmsg << std::endl;
    }
}

#ifdef DEBUG
#define LOG(...) Logger::log(__TIMESTAMP__, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#else
#define LOG(...)
#endif

#endif //_LOGGING_H_
