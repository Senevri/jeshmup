#ifndef _TEST
#include <iostream>
#include <UnitTest++.h>

#include "game.h"
#include "LevelFactory.h"
#include "world.h"

int run_tests(void)
{
    return UnitTest::RunAllTests();
}

int main( int argc, char *argv[] )
{
//    if( run_tests() )
//    {
//        return 5;
//    }
//    else
//    {
//        return 0;
//    }
    LevelFactory factory;
    World world;
    CMyGame *game = new CMyGame(world, factory);
    game->runGame();
    delete game;
    return 0;
}

#endif // not _TEST
