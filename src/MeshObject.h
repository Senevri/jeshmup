#ifndef MESHOBJECT_H
#define MESHOBJECT_H

#include "object.h"
#include "Point3d.h"

class Mesh;

class MeshObject : public Object
{
public:
    MeshObject(Mesh *mesh);
    virtual ~MeshObject();

    void update(int){};
    void draw(DrawEngine &engine);

	Point3d location();
	void location(Point3d);

private:
    Mesh *m_mesh;
	Point3d m_location;
};

#endif // MESHOBJECT_H
