#include "UnitTest++.h"

#include "HashMap.h"
#include "Conversion.h"

#include <string>

using namespace std;

SUITE(ListTestSuite)
{

	TEST(singleInsertAndGet)
	{
		HashMap<string, int> map;
		map.insert("test", 313);

		int testValue = map.get("test");
		CHECK( testValue == 313);
	}

	TEST(getInvlidValue)
	{
		HashMap<int,int> map;
		int test = map.get(7);
		CHECK(test == 0);

		map.insert(7, 7);
		test = map.get(313);
		CHECK( test == 0 );

		test= map.get(7);
		CHECK(test == 7);
	}

	TEST(multipleInsertAndGet)
	{
		HashMap<int, string> map;
		map.insert(313, "test");
		map.insert(313, "test");
		CHECK(map.size() == 1);

		string testIncrement = "testString";
		for( int i = 0; i < 500; ++i )
		{
			string insert = testIncrement + toString(i);
			map.insert(i, insert);
		}

		//the loop's insert overrides the previous 313 insert
		CHECK(map.size() == 500);

		for( int i = 0; i < 500; ++i )
		{
			string shouldBe = testIncrement + toString(i);
			string toTest = map.get(i);
			CHECK( shouldBe == toTest );
		}
	}
}