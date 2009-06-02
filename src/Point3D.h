#ifndef POINT3D_H
#define POINT3D_H

#include <GL/gl.h>

class Point3D
{
public:
    Point3D() : x(0.0f),y(0.0f),z(0.0f){}
    Point3D(GLfloat fx, GLfloat fy, GLfloat fz) : x(fx),y(fy),z(fz){}

    GLfloat x;
    GLfloat y;
    GLfloat z;
};

#endif // POINT3D_H
