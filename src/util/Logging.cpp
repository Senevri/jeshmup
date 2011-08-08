#include "Logging.h"

#include <iostream>

#ifdef _MSC_VER
#define _AFXDLL
#include <afx.h>
#endif

namespace Logger
{

void log(const char* timestamp, const char* file, const char* function, int line, ...)
{
    char fullMsg[1024];
    VA_ARGS_TO_CHAR(line, fullMsg);
#ifdef _MSC_VER
	TRACE("%s - %s - %s - %d - %s\n", timestamp, file, function, line, fullMsg);
#else
    std::clog << timestamp << " - " << file << " - " <<
            function << " - " << line << " - " <<
            fullMsg << std::endl;
#endif
}

void error(const char* timestamp, const char* file, const char* function, int line, ...)
{
    char fullMsg[1024];
    VA_ARGS_TO_CHAR(line, fullMsg);

#ifdef _MSC_VER
	TRACE("ERROR #: %s - %s - %s - %d - %s\n", timestamp, file, function, line, fullMsg);
#else
    std::clog << "#" << "ERROR" << "#: " << timestamp << " - " <<
            file << " - " << function << " - " << line << " - " <<
            fullMsg << std::endl;
#endif
}

};
