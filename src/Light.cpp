#include "Light.h"

#include "Color.h"

using namespace Color;

Light::Light()
{

}

Light::Light(Point3d position) : m_position(position)
{
}

Light::~Light()
{
    //nothing here yet, maybe never
}


Point3d Light::position() const
{
    return m_position;
}

void Light::setPosition(const Point3d position)
{
    m_position = position;
}

void Light::setPosition(const GLfloat x, const GLfloat y, const GLfloat z)
{
    m_position = Point3d(x, y, z);
}

void Light::setDiffuse(RGBA diffuse)
{
    m_diffuse = diffuse;
}

RGBA Light::diffuse()
{
    return m_diffuse;
}

void Light::setSpecular(RGBA specular)
{
    m_specular = specular;
}

RGBA Light::specular()
{
    return m_specular;
}

void Light::setAmbient(RGBA ambient)
{
    m_ambient = ambient;
}

RGBA Light::ambient()
{
    return m_ambient;
}

void Light::setDistant(bool isDistant)
{
    if(isDistant)
    {
        m_distant = 0.0f;
    }
    else
    {
        m_distant = 1.0f;
    }
}

bool Light::isDistant()
{
    return m_distant;
}

void Light::fillWithPosition(GLfloat *array)
{
    m_position.fillArray(array);
    array[3] = m_distant;
}

