#include "Timer.h"

#include "Logging.h"

#include <unistd.h>

unsigned long long AssemblyTimer::frequency = 0;

void AssemblyTimer::initFrequency()
{
    if( frequency )
    {
        return;
    }

    unsigned long long start;

    start = ticks();
    usleep(1000000);
    frequency = (ticks() -start) / 1000000;

    LOG("System freq estimate %d", frequency);
}

AssemblyTimer::AssemblyTimer() : m_startTicks(0)
{
    initFrequency();
}

AssemblyTimer::~AssemblyTimer()
{
}

void AssemblyTimer::start()
{
    m_startTicks = ticks();
}

unsigned int AssemblyTimer::elapsedTicks()
{
    return ticks() - m_startTicks;
}

unsigned int AssemblyTimer::microseconds()
{
    return (ticks() - m_startTicks) / frequency;
}

void AssemblyTimer::stop()
{
    m_startTicks = 0;
}

unsigned long long AssemblyTimer::ticks()
{
    unsigned long long value;
    __asm__(
            "rdtsc;"
            :"=A"(value)        /* output */
           );
    //LOG("Ticks: %u", value);
    //LOG("Sizeof:%u", sizeof(value));
    return value;
}
