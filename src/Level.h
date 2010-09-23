#ifndef LEVEL_H
#define LEVEL_H

#include <vector>

class Object;
class DrawableObject;

class Level
{
public:
    Level();
    virtual ~Level();

    void addObject(Object* object);
    const std::vector<Object*>& objects();

private:
    std::vector<Object*> m_objects;
};

#endif // LEVEL_H
