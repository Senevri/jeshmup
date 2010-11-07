#include "ChunkReader.h"

std::istream& operator>>(std::istream &is, ChunkId &chunkId)
{
	unsigned char id[4];
	unsigned char length[2];
	is.read((char*)id, sizeof(char)*4);
	is.read((char*)length, sizeof(char)*2);

	chunkId.m_id = CID(id[0], id[1],id[2],id[3]);
	chunkId.m_length = (unsigned short)length[0] << 8 | (unsigned short)length[1];

	return is;
}