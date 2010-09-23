/*
 *  3dsLoader.cpp
 *  jeshmup
 *
 *  Created by Jari Tauriainen on 8/19/08.
 *  Copyright 2008. All rights reserved.
 *
 */
#include "3dsLoader.h"

#include "3dsFileFormat.h"
#include "Mesh.h"
#include "MeshMaterial.h"
#include "Logging.h"

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

dsLoader::dsLoader(){

}

dsLoader::~dsLoader(){

}

Mesh* dsLoader::load(string file) {
    mInputFile.open(file.c_str(), ifstream::in | ifstream::binary);
    if(!mInputFile.is_open())
    {
        return 0;
    }
    // get length of file:
    mInputFile.seekg (0, ios::end);
    int length = mInputFile.tellg();
    mInputFile.seekg (0, ios::beg);
    LOG("File: %s length: %d", file.c_str(),length);

    openChunk();
    if(mChunkId != MAIN3DS){
        LOG("Cannot open MAIN3DS chunk!");
        return 0;
    }
    //main3ds is the main chunk containing the whole file
    openChunk();
    while(mChunkId != EDIT3DS && !mInputFile.eof())
    {
        nextChunk();
        openChunk();
    }

    if(mChunkId != EDIT3DS)
    {
        LOG("Cannot open EDIT3DS chunk!");
        return 0;
    }

    Mesh *mesh = new Mesh();
    openChunk();
    while(!finished() && mChunkId > 0)
    {
        switch(mChunkId)
        {
        case EDIT_OBJECT:
            {
                std::string name = readString();
                LOG("Object name: %s",name.c_str());
                mesh->setName(name);
                break;
            }
        case EDIT_MATERIAL:
            {
                loadMaterialChunk(mesh, mChunkLength);
            }
        case OBJ_TRIMESH:
            {
                //no data in chunk
                break;
            }
        case TRI_VERTEXL: //vertex data
            {
                ushort amount = readUShort();
                LOG("Object: %s vertices: %d",mesh->name().c_str(),amount);
                float *vertices = new float[amount*3];
                for(int i = 0; i < amount; i++)
                {
                    vertices[i*3] = readFloat();
                    vertices[i*3+1] = readFloat();
                    vertices[i*3+2] = readFloat();
                }
                mesh->meshFromFloatArray(vertices,amount*3);
                break;
            }
        case TRI_FACEL1: //face data
            {
                ushort amount = readUShort();
                LOG("Object: %s face caount: %d",mesh->name().c_str(),amount);
                ushort *faces = new ushort[amount*3];
                for(int i = 0; i < amount; i++)
                {
                    faces[i*3] = readUShort();
                    faces[i*3+1] = readUShort();
                    faces[i*3+2] = readUShort();
                    //face info not needed now,,,
                    readUShort();
                }
                mesh->setFaces(faces, Mesh::TRIANGLES, amount*3);
                break;
            }
        case MAPPING_COORDINATES_LIST:
            {
                ushort amount = readUShort();
                LOG("Object: %s mapping coords count: %d",
                    mesh->name().c_str(),amount);
                float *coords = new float[amount*2];
                for(int i = 0; i < amount; i++)
                {
                    coords[i*2] = readFloat();
                    coords[i*2+1] = readFloat();
                }
                mesh->setUVMap(coords,amount*2);
                break;
            }
        default:
            {
                //if we were not interested in a chunk, skip it altogether
                nextChunk();
            }
        }
        //open the next chunk, for the while loop
        openChunk();
    }
    
    mInputFile.close();
    return mesh;
}

void dsLoader::loadMaterialChunk(Mesh* mesh, int chunkLength)
{
    MeshMaterial material;
    openChunk();
    int readAmount = mChunkLength;
    while(readAmount < chunkLength)
    {
        switch(mChunkId)
        {
        case MATNAME:
            {
                std::string materialName = readString();
                LOG("Material found: %s", materialName.c_str());
                break;
            }
        case MATLUMINANCE:
            {
                Color::RGB ambient = loadColorChunk();
                break;
            }
        default:
            {
                nextChunk();
            }
        }
        openChunk();
        readAmount += mChunkLength;
    }
}

Color::RGB dsLoader::loadColorChunk()
{
    openChunk();
    Color::RGB color;
    if( mChunkId == 0x0011)
    {
        color.red = readChar() / 255.0f;
        color.green = readChar() / 255.0f;
        color.blue = readChar() / 255.0f;
    }
    openChunk();
    openChunk();
    openChunk();

}

bool dsLoader::finished()
{
    return mInputFile.eof();
}

uint dsLoader::readChunkLength()
{
    uint st = readUShort();
    st |= readUShort() << 8;
    return st;
}

ushort dsLoader::readChunkId()
{
    return readUShort();
}

std::string dsLoader::readString()
{
    std::string str;
    char c = readChar();
    while(c > 0)
    {
        str.push_back(c);
        c = readChar();
    }
    return str;
}

ushort dsLoader::readUShort(){
   ushort data;
   mInputFile.read((char*)&data,sizeof(ushort));
   return data;
}

float dsLoader::readFloat()
{
    float f;
    mInputFile.read((char*)&f,sizeof(float));
    return f;
}

uint dsLoader::readUInt(){
    uint value;
    mInputFile.read((char*)&value,sizeof(uint));
    return value;
}

char dsLoader::readChar()
{
    return mInputFile.get();
}

/*
 Try to keep all the chunk reader interface under here
 */
bool dsLoader::openChunk()
{
    mChunkId = readChunkId();
    mChunkLength = readChunkLength();
	return false; //FIXME
}

void dsLoader::nextChunk(){
    int toJump = mChunkLength - sizeof(mChunkLength) - sizeof(mChunkId);
    mInputFile.seekg(toJump, ios_base::cur);
}

