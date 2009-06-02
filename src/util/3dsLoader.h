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

#include <string>
#include <fstream>

class Mesh;

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
  
  //possible interface?!?
private:
  std::string readString();
  ushort readChunkId();
  uint readChunkLength();
  int readChunkPointer();
  bool findChunk(int,bool);
  void nextChunk();
  bool openChunk();
    
private:
  std::ifstream mInputFile;
  ushort mChunkId;
  uint mChunkLength;
};

#endif // _3DSLOADER_H_
