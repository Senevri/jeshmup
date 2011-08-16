#ifndef MESHMATERIAL_H
#define MESHMATERIAL_H

#include "Color.h"

struct MeshMaterial
{
    MeshMaterial();
    MeshMaterial(Color::RGB ambient,
                 Color::RGB diffuse,
                 Color::RGB specular);
    virtual ~MeshMaterial();

    Color::RGB ambient;
    Color::RGB diffuse;
    Color::RGB specular;
};

#endif // MESHMATERIAL_H
