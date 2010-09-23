#ifndef CHUNKREADER_H
#define CHUNKREADER_H

#include <iostream>

template<typename ChunkIdType>
struct Chunk
{
    Chunk(ChunkIdType chunkType, int chunkSize, char* chunkData)
        :
        type(chunkType),
        size(chunkSize),
        data(chunkData)
    {}

    ChunkIdType type;
    int size;
    char* data;
};

template<typename ChunkIdType, int ChunkTypeLength, int ChunkSizeLength>
class ChunkParser
{
    typedef Chunk<unsigned int> uChunk;
public:
    typedef void (*chunkFoundCallback)(uChunk* chunk);
public:
    ChunkParser();

    virtual void mainChunkFound(uChunk* chunk);
    void parseChunk(uChunk *chunk, chunkFoundCallback callback);
};

template<typename ChunkIDType, int ChunkTypeLength, int ChunkSizeLength>
class ChunkReader
{
public:
    ChunkReader();
    virtual ~ChunkReader();
};

#endif // CHUNKREADER_H
