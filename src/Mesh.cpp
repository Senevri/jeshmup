#include "Mesh.h"
//Mesh: surfaces in a 3d object, at least.
//TODO: Switch to internally using a list of verts + list of faces instead.

//public:
Mesh::Mesh(void)
{
}

Mesh::Mesh(std::vector<Mesh::vertex *> vpVertices, Mesh::format type)
{
	//let's copy
	this->m_data.assign(vpVertices.begin(), vpVertices.end());
	this->m_type = type;
}


Mesh::Mesh(std::string name)
{
	this->m_name = name;
}


Mesh::~Mesh(void)
{
	std::vector<vertex *>::iterator itr;
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
std::string Mesh::getName(){
	return this->m_name;
}

//std::vector<float *> Mesh::getMesh(){
//	std::vector<float *> output;
//	for each(vertex *v in this->m_data) {
//		float * arr = vertexToArray(*v); /* returns a pointer to an array */
//		output.push_back(arr); /* ...profit? */
//	}	
//	return output;
//}

Mesh::vertex * Mesh::vertexArrayFromMesh(void){
	std::vector<vertex *>::iterator itr;
	unsigned int size = m_data.size();
	vertex *v = new vertex[(const int)size]; /* cannot allocate since we don't know size...*/
	int i = 0;
	for ( itr = m_data.begin(); itr < m_data.end(); ++itr )
	{	
		v[i] = **itr; /* so many pointer ops in c++ project ... nojustno */
		i++;
	}
	return v;
}

std::vector<Mesh::vertex *> Mesh::getMeshVertices(){
	return this->m_data;
}


void Mesh::meshFromFloatArray(const float * mesh, format type, int mesh_size){
	this->m_type = type;
	for(int i = 0; i<mesh_size;i+=3){
		vertex *v = new vertex;
		v->x = mesh[i];
		v->y = mesh[i+1];
		v->z = mesh[i+2];
		this->m_data.push_back(v);
	}
	return;
}
//private:
float * Mesh::vertexToArray(vertex v){
	float output[3];
	output[0] = v.x;
	output[1] = v.y;
	output[2] = v.z;
	return output; /* gets warning, but seems to return correct data...*/
}

