/*
 * Mesh.h
 * by: Esa Karjalainen
 * has: Mesh as in array of vertices, manipulating them, and knowing stuff about them.
 *		maybe add texture stuff here too?
 */

#ifndef _MESH_H_
#define _MESH_H_

#include <vector>
#include <string>

class Mesh
{
public:
    enum Format{ POINTS = 1, TRIANGLES = 3, QUADS = 4 };

    struct Vertex{
		float x;
		float y;
		float z;
    };

    struct UVCoordinate
    {
        float u;
        float v;
        unsigned int vertexIndex;
    };

    struct Face
    {
        unsigned int *vertices;
        Mesh::Format format;
    };
	
	Mesh(void);
    Mesh(std::vector<Mesh::Vertex *> vpVertices, Mesh::Format type);
    Mesh(std::string name);
    Mesh(Mesh::Format format);
	~Mesh(void);
	
	int getType();
    std::string name();
    void setName(std::string name);

	//std::vector<float *> getMesh(); /*FIXME: does not work: do not use*/
    std::vector<Vertex *> vertices();
    std::vector<Face*> faces();
    void setFaces(const unsigned short *faces, Mesh::Format type, int length);
    void setUVMap(const float *coords, int length);
    void meshFromFloatArray(const float * mesh, int mesh_size);
    Vertex* vertexArrayFromMesh(void);
	
private:	
    std::vector<Vertex *> m_data;
	/* todo: list of verts + list of faces, better? */
    std::vector<Vertex *> m_vpVertices;
    std::vector<Face *> m_fpFaces;
    std::vector<UVCoordinate*> m_uvCoordinates;
    std::string m_name;

	int m_type;
    float* vertexToArray(Vertex v);
};

#endif // _MESH_H
