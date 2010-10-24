#include "MeshObject.h"

#include "DrawEngine.h"
#include "Point3d.h"

MeshObject::MeshObject(Mesh *mesh) : m_mesh(mesh), visible(true)
{
}

MeshObject::~MeshObject()
{
}

void MeshObject::draw(DrawEngine &engine)
{

    //engine.renderMesh(*m_mesh);
	if(this->visible){
		engine.renderMeshAt(*m_mesh, m_location);
	}
}

Point3d MeshObject::location(){
	return this->m_location;
}
void MeshObject::location(Point3d location){
	this->m_location = location;
}