#include "JMFImport.h"

#include "ChunkReader.h"
#include "Mesh.h"
#include "Logging.h"
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <iostream>

const unsigned int JMFImport::CHUNK_JMF = CID( 'J','M','F','M' );
const unsigned int JMFImport::CHUNK_VERT = CID( 'V','E','R','T' );
const unsigned int JMFImport::CHUNK_POLY = CID( 'P','O','L','S' );

JMFImport::JMFImport(const std::string &fileName) : m_fileName(fileName), m_mesh(0)
{

}

JMFImport::~JMFImport(void)
{
}

bool JMFImport::import()
{
	if( m_mesh )
	{
		//LOG_ERROR("Already loaded mesh: %s", m_mesh->name());
		return false;
	}

	m_mesh = new Mesh(m_fileName);

	bool success = false;
	std::ifstream file(m_fileName.c_str(), std::ios::in | std::ios::binary);
	if (file.is_open())
	{
		ChunkId main;
		file >> main;
		if( main.id() == CHUNK_JMF )
		{
			success = readMesh(file);
			if( !success )
			{
				delete m_mesh;
			}
		}
		else
		{
			LOG_ERROR("File \"%s\" not a JMF model file!", m_fileName.c_str());
		}
	}
	else
	{
		LOG_ERROR("Cannot open file: %s", m_fileName.c_str());
	}

	return success;
}

bool JMFImport::readMesh( std::ifstream &file )
{
	bool success = false;

	ChunkId temp;
	file >> temp;

	if( temp.id() == CHUNK_VERT )
	{
		float *array = (float*)malloc(temp.length() * sizeof(float));
		ChunkReader::readBigEndianData(array, file, temp.length());
		m_mesh->meshFromFloatArray(array, temp.length() / sizeof(float));
		free(array);

		file >> temp;

		if( temp.id() == CHUNK_POLY )
		{
			unsigned int *polys = (unsigned int*)malloc(temp.length() * sizeof(unsigned int));
			ChunkReader::readBigEndianData(polys, file, temp.length());
			m_mesh->setFaces(polys, Mesh::TRIANGLES, temp.length() / sizeof(unsigned int));
			free(polys);

			success = true;
		}
		else
		{
			LOG_ERROR("Could not locate poly chunk at correct location!");
		}
	}
	else
	{
		LOG_ERROR("Could not locate vertex chunk at correct location!");
	}
	
	return success;
}

Mesh* JMFImport::mesh() const
{
	return m_mesh;
}
