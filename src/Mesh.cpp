#include "Mesh.h"


//public:
Mesh::Mesh(void)
{
}

Mesh::Mesh(std::string name)
{
	m_name = name;
}


Mesh::~Mesh(void)
{
	for each (vertex *v in m_data){
		/*FIXME: for some reason breaks */
		//if(v)
		//	delete v; 
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
	return output;
}

