#include "Level.h"

Level::Level()
{

}

Level::~Level()
{

}

void Level::addObject(Object *object)
{
    m_objects.push_back(object);
}

const std::vector<Object*>& Level::objects()
{
    return m_objects;
}
