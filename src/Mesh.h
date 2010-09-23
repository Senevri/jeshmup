/*
 * Mesh.h
 * by: Esa Karjalainen
 * has: Mesh as in array of vertices, manipulating them, and knowing stuff about them.
 *		maybe add texture stuff here too?
 */

#pragma once

#include "Point3d.h"
#include "Vector.h"

#include <vector>
#include <string>

namespace Color
{
    class RGB;
};

class Mesh
{
public:
    enum Format{ POINTS = 1, TRIANGLES = 3, QUADS = 4 };

    /**
      * Typedef of point to vertex as it is more describing here.
      */
    typedef Point3d Vertex;

    /**
      * Simple structure for UV coordinates.
      */
    struct UVCoordinate
    {
        float u;
        float v;
        unsigned int vertexIndex;
    };

    /**
      * Structure to define a polygon via indices to list of vertices.
      */
    struct Face
    {
        /**
          * Destructor.
          */
        ~Face()
        {
            delete indices;
        }

        unsigned int *indices;
        Mesh::Format format;

        /**
          * Calculates this faces normal vector with the given
          * vertex list. The face indices must match the given vertices vector.
          * @param vertices The std::vector of vertex data to use to calculate
          * the normal
          * @return The normal vector of the face
          */
        Vector faceNormal(std::vector<Mesh::Vertex*>& vertices)
        {
            return Vector::normalVector(*vertices[indices[0]],
                                        *vertices[indices[1]],
                                        *vertices[indices[2]]);
        }
    };
	
	Mesh(void);
    Mesh(std::vector<Mesh::Vertex *> vpVertices, Mesh::Format type);
    Mesh(std::string name);
    Mesh(Mesh::Format format);
	~Mesh(void);
	

	void setType(Mesh::Format type);
    int getType() const;
    std::string name() const;
    void setName(std::string name);

    void setMaterial(Color::RGB ambient,
                     Color::RGB diffuse,
                     Color::RGB specular);

	//std::vector<float *> getMesh(); /*FIXME: does not work: do not use*/
    std::vector<Vertex *> vertices() const;
    std::vector<Face*> faces() const;
    void setFaces(const unsigned short *faces, Mesh::Format type, int length);
    void setUVMap(const float *coords, int length);
    void meshFromFloatArray(const float * mesh, int mesh_size);
    Vertex* vertexArrayFromMesh(void) const;
	
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
