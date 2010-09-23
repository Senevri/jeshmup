#ifndef MESHOBJECT_H
#define MESHOBJECT_H

#include "object.h"

class Mesh;

class MeshObject : public Object
{
public:
    MeshObject(Mesh *mesh);
    virtual ~MeshObject();

    void update(int){};
    void draw(DrawEngine &engine);

private:
    Mesh *m_mesh;
};

#endif // MESHOBJECT_H
