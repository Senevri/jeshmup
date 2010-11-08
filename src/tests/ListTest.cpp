#include "UnitTest++.h"

#include "List.h"
#include "Conversion.h"

#include <string>

using namespace std;

SUITE(ListTestSuite)
{

TEST(appendOne)
{
    string test("test");
    BruteList<string> list;
    list.append(test);

    CHECK(list.size() == 1);

    string result = list.at(0);
    CHECK(result == test);
}

TEST(appendMany)
{
    BruteList<string> list;
    string testIncrement("test");
    for(int i = 0; i < 1000; ++i)
    {
        string insert = testIncrement + toString<int>(i);
        list.append(insert);
    }

    for(int i = 999; i >= 0; --i)
    {
        string result = list.at(i);
        CHECK(result == (testIncrement + toString<int>(i)));
    }
}

}

SUITE(LinkedListTestSuite)
{

	TEST(append)
	{
		string test("test");
		LinkedList<string> list;
		list.append(test);

		string at = list.at(0);

		CHECK( test == at);

		list.append("test2");
		list.append("test3");
		list.append("test3");

		at = list.at(2);
		CHECK( at == "test3" );
		at = list.at(3);
		CHECK( at == "test3" );

		//empty value should be returned
		at = list.at(1234);
		CHECK( at == "" );
	}

	TEST(remove)
	{
		LinkedList<string> list;
		list.append("test0");
		list.append("test1");
		list.append("test2");
		list.append("test3");
		list.append("test4");

		list.remove(1);
		string at = list.at(1);
		CHECK( at == "test2" );

		list.remove(3);
		at = list.at(2);
		CHECK( at == "test3" );

		CHECK(list.size() == 3 );

		list.remove(0);
		at = list.at(0);
		CHECK( at == "test2" );
		CHECK( list.size() == 2);

		//no crash
		list.remove(12123);
	}

}
