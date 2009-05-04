/*
 *  3dsLoader.h
 *  jeshmup
 *
 *  Created by Jari Tauriainen on 8/19/08.
 *  Copyright 2008. All rights reserved.
 *
 */

#ifdef _WINDOWS
	typedef unsigned int uint;
	typedef unsigned short ushort;
#endif

class dsLoader
{
public:
  dsLoader(void);
  ~dsLoader(void);
  void load(string file);
private:
  uint ReadUInt();
  ushort ReadUShort();
  char ReadChar();
  
  //possible interface?!?
private:
  int ReadChunkId();
  int ReadChunkPointer();
  bool FindChunk(int,bool);
  int NextChunk();
  bool OpenChunk(int);
    
private:
  ifstream mInputFile;
  long mChunkPointer;
};