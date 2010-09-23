#include "MeshObject.h"

#include "DrawEngine.h"
#include "Point3d.h"

MeshObject::MeshObject(Mesh *mesh) : m_mesh(mesh)
{
}

MeshObject::~MeshObject()
{
}

void MeshObject::draw(DrawEngine &engine)
{
    engine.renderMesh(*m_mesh);
}
