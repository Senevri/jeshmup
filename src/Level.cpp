#include "Level.h"

Level::Level()
{

}

Level::~Level()
{
    m_objects.clear();
    m_lights.clear();

}

void Level::addObject(Object *object)
{
    m_objects.push_back(object);
}

/* hack for testing*/


const std::vector<Object*>& Level::objects()
{
    return m_objects;
}
void Level::addLight(Light *light)
{
    m_lights.push_back(light);
}

/* hack for testing*/


const std::vector<Light*>& Level::lights()
{
    return m_lights;
}
