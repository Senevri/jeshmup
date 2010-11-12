#include "MeshObject.h"

#include "DrawEngine.h"
#include "Point3d.h"

MeshObject::MeshObject(Mesh *mesh) : m_mesh(mesh), visible(true), m_arotation(0)
{
}

MeshObject::~MeshObject()
{
}

void MeshObject::draw(DrawEngine &engine)
{

    //engine.renderMesh(*m_mesh);
	if(this->visible){
		engine.renderMeshAt(*m_mesh, m_location, m_arotation, m_vrotation);
	}
}

Point3d MeshObject::location()
{
	return this->m_location;
}

void MeshObject::location(const Point3d &location){
	this->m_location = location;
}
void MeshObject::rotation(const float angle, const Point3d &vector){
	this->m_arotation = angle;
	this->m_vrotation = vector;
}
