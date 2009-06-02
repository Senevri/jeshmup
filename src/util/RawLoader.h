#ifndef _RAWLOADER_H_
#define _RAWLOADER_H_

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
 * thus, a quad is described as 
 * "%.6f %.6f %.6f %.6f\n"
 * a triangle as "%.6f %.6f %.6f\n"
 */

class RawLoader
{
public:
	RawLoader(void);
	~RawLoader(void);
    Mesh::Vertex * quadToTriangle(Mesh::Vertex * quad);
	bool load(std::string filename);
    std::vector<Mesh::Vertex *> getVertices(void);

private:
	float strToFloat(std::string);
	std::ifstream m_InputFile;
    std::vector<Mesh::Vertex *> m_vpVertices;
};

#endif //_RAWLOADER_H_
