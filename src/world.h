
/**
 * ZA WARUDO: 
 * Contains a list of objects and their locations, and so on...
 *  - Object statuses?
 *  - functions for manipulating, loading, saving, etc. of the world
 **/
#ifndef _WORLD_H_
#define _WORLD_H_

#include "object.h"
#include "Vector.h"
#include <vector>
#include <string>

class World {
public:

    World();
    ~World();

    void start(std::vector<Object*> objects);
    void updateWorld(int ticks);

private:
    std::vector<Object*> m_objects;
};

#endif //_WORLD_H_
