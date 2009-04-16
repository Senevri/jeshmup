#include <iostream>
//#include "SDL.h"
#include "game.h"
#include "UnitTest++.h"

int main( int argc, char *argv[] )
{
	game = new CMyGame();
	g->runGame();
	delete game;	
	return 0;
}

