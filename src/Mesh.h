#pragma once
#include <vector>
#include <string>

class Mesh
{
public:
	Mesh(void);
	Mesh(std::string);
	~Mesh(void);

	std::string m_name;

	enum format{ POINTS, TRIANGLES, QUADS };

	typedef struct {
		float x;
		float y;
		float z;
	} vertex;

	int getType();
	std::string getName();
	//std::vector<float *> getMesh(); /*FIXME: does not work: do not use*/
	std::vector<vertex *> getMeshVertices();
	void meshFromFloatArray(const float * mesh, format type, int mesh_size);
	
private:	
	std::vector<vertex *> m_data;
	int m_type;
	float * vertexToArray(vertex v);
};
