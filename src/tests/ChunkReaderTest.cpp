#include "UnitTest++.h"

#include "ChunkReader.h"

SUITE(ChunkReaderTestSuite)
{
	TEST(CheckChunkId)
	{
		ChunkId test('a','b','e','f');
		unsigned int intValue = 'a' << 24 | 'b' << 16 | 'e' << 8 | 'f';

		CHECK(test.id() == intValue);
	}

	TEST(CheckChunkIdString)
	{
		ChunkId test('a','b','e','f');
		std::string idAsString = test.toString();

		CHECK(0 == idAsString.compare("abef"));
	}

}