#pragma once
#include <vector>
#include <string>

class Mesh
{
public:
	typedef struct {
		float x;
		float y;
		float z;
	} vertex;
	enum format{ POINTS, TRIANGLES, QUADS };
	
	Mesh(void);
	Mesh(std::vector<Mesh::vertex *> vpVertices, Mesh::format type);
	Mesh(std::string);
	~Mesh(void);

	std::string m_name;

	
	typedef struct {
		vertex vertices[3];
	} triangle;

	typedef struct {
		vertex vertices[4];
	} quad;

	int getType();
	std::string getName();
	//std::vector<float *> getMesh(); /*FIXME: does not work: do not use*/
	std::vector<vertex *> getMeshVertices();
	void meshFromFloatArray(const float * mesh, format type, int mesh_size);
	vertex * vertexArrayFromMesh(void);
	
private:	
	std::vector<vertex *> m_data;
	int m_type;
	float * vertexToArray(vertex v);
};
