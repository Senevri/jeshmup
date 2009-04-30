#include <iostream>
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

	TEST(FailAlways){
		CHECK(false);
	}
}
;

int main(int argc, char * argv[]){
	return UnitTest::RunAllTests();
}
