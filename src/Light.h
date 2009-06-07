#pragma once

#include "Point3d.h"
#include "Color.h"

#include <GL/gl.h>

class Light
{
public:
    Light();
    Light(Point3d position);

    virtual ~Light();

    Point3d virtual position() const;
    void virtual setPosition(const Point3d position);
    void virtual setPosition(const GLfloat x, const GLfloat y, const GLfloat z);

    void virtual setSpecular(Color::RGBA specular);
    Color::RGBA virtual specular();

    void virtual setDiffuse(Color::RGBA diffuse);
    Color::RGBA virtual diffuse();

    void virtual setAmbient(Color::RGBA ambient);
    Color::RGBA virtual ambient();

    void virtual setDistant(bool isDistant);
    bool virtual isDistant();

    void virtual fillWithPosition(GLfloat *array);

protected:
    Point3d m_position;

    GLfloat m_distant;

    Color::RGBA m_specular;
    Color::RGBA m_diffuse;
    Color::RGBA m_ambient;
};
