#include "Mesh.h"

#include <assert.h>

//Mesh: surfaces in a 3d object, at least.
//TODO: Switch to internally using a list of verts + list of faces instead.

//public:
Mesh::Mesh(void)
{
}

Mesh::Mesh(std::vector<Mesh::Vertex *> vpVertices, Mesh::Format type)
{
	//let's copy
	this->m_data.assign(vpVertices.begin(), vpVertices.end());
	this->m_type = type;
}

Mesh::Mesh(Mesh::Format format)
{
    m_type = format;
}


Mesh::Mesh(std::string name)
{
	this->m_name = name;
}


Mesh::~Mesh(void)
{
    std::vector<Vertex *>::iterator itr;
	for ( itr = m_data.begin(); itr < m_data.end(); ++itr )
	{	
		/*FIXME: for some reason breaks */
		//delete *itr;
	}
}

int Mesh::getType(){
	return this->m_type;
}

/* m_name is public, but for completion's sake... */
std::string Mesh::name(){
	return this->m_name;
}

void Mesh::setName(std::string name)
{
    m_name = name;
}

//std::vector<float *> Mesh::getMesh(){
//	std::vector<float *> output;
//	for each(Vertex *v in this->m_data) {
//		float * arr = VertexToArray(*v); /* returns a pointer to an array */
//		output.push_back(arr); /* ...profit? */
//	}	
//	return output;
//}

Mesh::Vertex * Mesh::vertexArrayFromMesh(void){
    std::vector<Vertex *>::iterator itr;
	unsigned int size = m_data.size();
    Vertex *v = new Vertex[(const int)size]; /* cannot allocate since we don't know size...*/
	int i = 0;
	for ( itr = m_data.begin(); itr < m_data.end(); ++itr )
	{	
		v[i] = **itr; /* so many pointer ops in c++ project ... nojustno */
		i++;
	}
	return v;
}

std::vector<Mesh::Vertex *> Mesh::vertices()
{
	return this->m_data;
}

std::vector<Mesh::Face*> Mesh::faces()
{
    return this->m_fpFaces;
}

void Mesh::setFaces(const unsigned short *faces, Mesh::Format type, int facesSize)
{
    for(int i = 0; i < facesSize; i += type)
    {
        Face *f = new Face;
        unsigned int* tmpFace = new unsigned int[type];
        for(int j = 0; j < type; j++)
        {
            tmpFace[j] = faces[i+j];
        }
        f->indices = tmpFace;
        f->format = type;
        m_fpFaces.push_back(f);
    }
}

void Mesh::setUVMap(const float *coords, int length)
{
    assert(length % 2 == 0);
    int amount = length /2;
    for(int i = 0; i < length; i+=2)
    {
        UVCoordinate *uv = new UVCoordinate;
        uv->u = coords[i];
        uv->v = coords[i+1];
        uv->vertexIndex = i;

        m_uvCoordinates.push_back(uv);
    }
}

void Mesh::meshFromFloatArray(const float *mesh, int mesh_size)
{
    for(int i = 0; i<mesh_size; i += 3){
        Vertex *v = new Vertex;
		v->x = mesh[i];
		v->y = mesh[i+1];
		v->z = mesh[i+2];
		this->m_data.push_back(v);
	}
	return;
}
//private:
float* Mesh::vertexToArray(Vertex v)
{
    float* output = new float[3];
	output[0] = v.x;
	output[1] = v.y;
	output[2] = v.z;
	return output; /* gets warning, but seems to return correct data...*/
}

