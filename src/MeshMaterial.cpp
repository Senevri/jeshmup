#include "MeshMaterial.h"

using namespace Color;

MeshMaterial::MeshMaterial()
    :
    ambient(RGB()),
    diffuse(RGB()),
    specular(RGB())
{
}


MeshMaterial::MeshMaterial(RGB ambient,
                           RGB diffuse,
                           RGB specular)
                               :
                          ambient(ambient),
                          diffuse(diffuse),
                          specular(specular)

{
}

MeshMaterial::~MeshMaterial()
{

}
