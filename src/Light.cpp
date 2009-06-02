#include "Light.h"

Light::Light()
{

}

Light::Light(Point3D position) : m_position(position)
{
}

Light::~Light()
{
    //nothing here yet, maybe never
}


Point3D Light::position() const
{
    return m_position;
}

void Light::setPosition(const Point3D position)
{
    m_position = position;
}

void Light::setPosition(const GLfloat x, const GLfloat y, const GLfloat z)
{
    m_position = Point3D(x,y,z);
}
