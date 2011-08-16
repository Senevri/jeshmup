#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <Light.h>

class Object;
class DrawableObject;

class Level
{
public:
    Level();
    virtual ~Level();

    void addObject(Object* object);
    const std::vector<Object*>& objects();
    void addLight(Light* light);
    const std::vector<Light*>& lights();

private:
    std::vector<Object*> m_objects;
    std::vector<Light*> m_lights;
};

#endif // LEVEL_H
