#pragma once
#include "../Mesh.h"
#include <iostream>
#include <fstream>

/**
 * RawLoader.h
 * Just because.
 * - Esa Karjalainen
 */

/**	Raw File Format description AFAIK:
 * plaintext, 
 * Each face is described in a single line, terminated by a newline
 * Each coordinate is separated by a space " " character.
 * this, a quad is described as 
 * "%.6f %.6f %.6f %.6f\n"
 * a triangle as "%.6f %.6f %.6f\n"
 */

class RawLoader
{
public:
	RawLoader(void);
	~RawLoader(void);
	Mesh::vertex * quadToTriangle(Mesh::vertex * quad);
	bool load(std::string filename);
	std::vector<Mesh::vertex *> getVertices(void);

private:
	float strToFloat(std::string);
	std::ifstream m_InputFile;
	std::vector<Mesh::vertex *> m_vpVertices;
};
