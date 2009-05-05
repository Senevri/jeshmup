#ifdef _TEST
#include <iostream>
#include "SDL.h"
#include "UnitTest++.h"
#include "world.h"

using namespace std;

SUITE(ZaWarudoTests) {
	TEST(InitTest){
		cout << "ZA WARUDO TESTS\n";
		Object *o = new Object();
		o->name = "test object";
		o->coord.x = 10;
		o->coord.y = 20;
		o->coord.z = 30;
		CHECK(0==o->name.compare("test object"));
		delete o;
	}
}
;

int main(int argc, char * argv[]){
	int result = 0;
	result = UnitTest::RunAllTests();
	cin.get();
	return result;
}
#endif //_TEST

