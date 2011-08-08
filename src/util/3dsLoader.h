/*
 *  3dsLoader.h
 *  jeshmup
 *
 *  Created by Jari Tauriainen on 8/19/08.
 *  Copyright 2008. All rights reserved.
 *
 */
#ifndef _3DSLOADER_H_
#define _3DSLOADER_H_

#include "Definitions.h"

#include <fstream>

class Mesh;

namespace Color
{
    class RGB;
};

class dsLoader
{
public:
  dsLoader(void);
  ~dsLoader(void);
  Mesh* load(std::string file);
private:
  uint readUInt();
  ushort readUShort();
  float readFloat();
  char readChar();
  bool finished();

private:
  void loadMaterialChunk(Mesh* mesh, int chunkLength);
  Color::RGB loadColorChunk();
  std::string readString();
  ushort readChunkId();
  uint readChunkLength();
  void nextChunk();
  bool openChunk();
    
private:
  std::ifstream mInputFile;
  ushort mChunkId;
  uint mChunkLength;
};

#endif // _3DSLOADER_H_
