#ifndef CHUNKREADER_H
#define CHUNKREADER_H

#include <istream>

#define CID(a,b,c,d) (((unsigned int)a << 24 | (unsigned int)b << 16 | (unsigned int)c << 8 | (unsigned int)d))

struct ChunkId
{
	ChunkId() : m_id(0), m_length(0)
	{

	}

	ChunkId(unsigned char a,
			unsigned char b,
			unsigned char c,
			unsigned char d)
	:
	m_id(CID(a,b,c,d))
	{

	}

	ChunkId( unsigned int id, int length) 
		:
	m_id(id),
	m_length(length)
	{
	}

	std::string toString() const
	{
		char id[5];
		id[0] = m_id >> 24;
		id[1] = (m_id >> 16) & 0xFF;
		id[2] = (m_id >> 8) & 0xFF;
	    id[3] = m_id & 0xFF;
		id[4] = 0;

		return std::string(id);
	}

	unsigned int id() const
	{
		return m_id;
	}
	unsigned int length() const
	{
		return m_length;
	}

private:
	friend std::istream& operator>>(std::istream &is, ChunkId &chunkId);
	unsigned int m_id;
	unsigned short m_length;
};

std::istream& operator>>(std::istream &is, ChunkId &chunkId);

class ChunkReader
{
public:
	template<typename T>
	static void swapBytes(T *data, size_t amount)
	{
		size_t half = amount / 2;
		unsigned char* raw = (unsigned char*)data;

		for(unsigned int i = 0; i < half ; ++i)
		{
			unsigned char temp = raw[i];
			raw[i] = raw[amount-1-i];
			raw[amount-1-i] = temp;
		}
	}

	template<typename T>
	static int readBigEndianData(T* dest, std::istream &istream, size_t byteAmount)
	{
		//this must be optimized if it gets too slow, duh
		for( unsigned int i = 0; i < byteAmount / sizeof(T); ++i )
		{
			T f = 0.0f;
			istream.read((char*)&f, sizeof(T));
			ChunkReader::swapBytes(&f, sizeof(T));
			dest[i] = f;
		}
		return byteAmount -1;
	}
};

#endif // CHUNKREADER_H
