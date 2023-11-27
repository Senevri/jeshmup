#ifndef _TEST
#include <iostream>
#include <UnitTest++.h>

#include "Logging.h"
#include "game.h"
#include "LevelFactory.h"
#include "world.h"

int run_tests(void)
{
    return UnitTest::RunAllTests();
}

int main( int argc, char *argv[] )
{
    LevelFactory factory;
    World world;
    MyGame *game = new MyGame(world, factory);
    game->runGame();
    delete game;
    return 0;
}

#endif // not _TEST
