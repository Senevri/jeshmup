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
	void location(const Point3d &location);
	void setVisibility(bool val){ this->visible=val; }
	void rotation(const float rotation, const Point3d &vector);

private:
    Mesh *m_mesh;
	float m_arotation;
	Point3d m_vrotation;
	Point3d m_location;
	bool visible:true;
};

#endif // MESHOBJECT_H
