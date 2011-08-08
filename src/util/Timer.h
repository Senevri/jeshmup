#ifndef TIMER_H
#define TIMER_H

class AssemblyTimer
{
public:
    static unsigned long long ticks();
    static unsigned long long frequency;
    void initFrequency();

public:
    AssemblyTimer();
    ~AssemblyTimer();

    void start();
    unsigned int elapsedTicks();
    unsigned int microseconds();
    unsigned long long longIntervalMicroseconds();
    void stop();



private:
    unsigned long long m_startTicks;
};

typedef AssemblyTimer Timer;

#endif // TIMER_H
