#include <iostream>
//#include "SDL.h"
#include "game.h"
#include "UnitTest++.h"

//Private declarations
int run_tests(void);

//Implementations start here
//
SUITE(MyTestSuite){
	TEST(Autosucceed){
		CHECK(true);
	}

	TEST(AutoFail){
		CHECK(false);
	}
}


/* Main Function
 *
 */
int main( int argc, char *argv[] )
{
	run_tests();
	std::string str_test = "";
	std::cin>>str_test;
	CMyGame * game = new CMyGame();
	game->runGame();
	delete game;	
	return 0;
}

int run_tests(void){
	return UnitTest::RunAllTests();
}

