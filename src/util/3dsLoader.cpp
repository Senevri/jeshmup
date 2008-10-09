/*
 *  3dsLoader.cpp
 *  jeshmup
 *
 *  Created by Jari Tauriainen on 8/19/08.
 *  Copyright 2008. All rights reserved.
 *
 */
#include<string>
#include<iostream>
#include<fstream>
using namespace std;

#include "3dsFileFormat.h"
#include "3dsLoader.h"

dsLoader::dsLoader(void){

}

dsLoader::~dsLoader(void){

}

void dsLoader::load(string file) {
    mInputFile.open(file.c_str(), ios::binary);
    if(!mInputFile.is_open()){
        return;
    }
    bool main = OpenChunk(MAIN3DS);
    if(!main){
        return;
    }
    bool edit = FindChunk(EDIT3DS,false);
    
    
}

ushort dsLoader::ReadUShort(){
  ushort first = ReadChar();
  ushort second = ReadChar();
  second << 8;
  return second or first;
}

uint dsLoader::ReadUInt(){
  uint value = ReadChar();
  value = ReadChar() | (value<<8);
  value = ReadChar() | (value<<8);
  value = ReadChar() | (value<<8);
  return value;
}

char dsLoader::ReadChar(){
  return mInputFile.get();
}

/*
 Try to keep all the chunk reader interface under here
 */
bool dsLoader::OpenChunk(int chunkID){
  int id = ReadChunkId();
  if(id != chunkID){
    return false;
  }
  mChunkPointer = ReadChunkPointer();
  return true;
}

int dsLoader::ReadChunkId(){
  return ReadUShort();
}

int dsLoader::ReadChunkPointer(){
  return ReadUInt();   
}

int dsLoader::NextChunk(){
  mInputFile.seekg(mChunkPointer - sizeof(mChunkPointer));
  int id = ReadChunkId();
  mChunkPointer = ReadChunkPointer();
  return id;
}

bool dsLoader::FindChunk(int chunk_id, bool beginning){
  if(beginning){
    mInputFile.seekg(0);
    mChunkPointer = -1;
  }
  
  
}