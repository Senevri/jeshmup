/*
 * Mesh.h
 * by: Esa Karjalainen
 * has: Mesh as in array of vertices, manipulating them, and knowing stuff about them.
 *		maybe add texture stuff here too?
 */

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
		vertex * vertices;
		Mesh::format format;
	} face;
	
	int getType();
	std::string getName();
	//std::vector<float *> getMesh(); /*FIXME: does not work: do not use*/
	std::vector<vertex *> getMeshVertices();
	void meshFromFloatArray(const float * mesh, format type, int mesh_size);
	vertex * vertexArrayFromMesh(void);
	
private:	
	std::vector<vertex *> m_data;
	/* todo: list of verts + list of faces, better? */
	std::vector<vertex *> m_vpVertices;
	std::vector<face *> m_fpFaces;
	
	int m_type;
	float * vertexToArray(vertex v);
};
