#ifndef LIGHT_H
#define LIGHT_H

#include "Point3D.h"

#include <GL/gl.h>

class Light
{
public:
    Light();
    Light(Point3D position);

    virtual ~Light();

    Point3D position() const;
    void setPosition(const Point3D position);
    void setPosition(const GLfloat x, const GLfloat y, const GLfloat z);

private:
    Point3D m_position;
};

#endif // LIGHT_H
