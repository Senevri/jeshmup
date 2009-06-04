#pragma once

#include "Light.h"
#include "Point3d.h"

class DirectionalLight : public Light
{
public:
    DirectionalLight();
    DirectionalLight(Point3d position, Point3d target);

    virtual ~DirectionalLight();

    void virtual setTarget(Point3d target);
    Point3d virtual target();

protected:
    Point3d m_target;

};

