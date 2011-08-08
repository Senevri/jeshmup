/** ZA WARUDO implementations 
 **/
#include "world.h"
#include "object.h"

#include <vector>

using namespace std;

World::World() {
}

World::~World(){
}

void World::start(std::vector<Object *> objects)
{
    m_objects = objects;
}

void World::updateWorld(int ticks)
{
    vector<Object*>::const_iterator i;
    vector<Object*>::const_iterator end = m_objects.end();
    for(i = m_objects.begin(); i != end; ++i)
    {
        Object *object = *i;
        object->update(ticks);
    }
}
