#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
{
}

DirectionalLight::DirectionalLight(Point3d position, Point3d target)
        : Light(position), m_target(target)
{
}

DirectionalLight::~DirectionalLight()
{

}

void DirectionalLight::setTarget(Point3d target)
{
    m_target = target;
}

Point3d DirectionalLight::target()
{
    return m_target;
}
