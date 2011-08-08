#include "UnitTest++.h"
#include "Timer.h"

#include <iostream>
#include <unistd.h>

SUITE(TimerTestSuite)
{

TEST(MatchSecond)
{
    Timer timer;
    timer.start();
    usleep(1000000);
    CHECK_CLOSE(1000000u, timer.microseconds(), 100);
    std::cout << "Slept:" << timer.microseconds() << std::endl;
}

}
