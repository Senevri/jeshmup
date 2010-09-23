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
