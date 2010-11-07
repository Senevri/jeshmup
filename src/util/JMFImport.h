#ifndef _JMFIMPORT_H
#define _JMFIMPORT_H

#include <string>

class Mesh;

class JMFImport
{
	static const unsigned int CHUNK_JMF;
	static const unsigned int CHUNK_VERT;
	static const unsigned int CHUNK_POLY;

public:
	JMFImport(const std::string &fileName);
	~JMFImport(void);

	bool import();
	Mesh* mesh() const;

private:
	bool readMesh( std::ifstream &file);

private:
	std::string m_fileName;
	Mesh *m_mesh;
};

#endif //_JMFIMPORT_H