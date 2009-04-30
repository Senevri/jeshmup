
/**
 * ZA WARUDO: 
 * Contains a list of objects and their locations, and so on...
 *  - Object statuses?
 *  - functions for manipulating, loading, saving, etc. of the world
 **/
#include "object.h"
#include <vector>

class World {
	public:
	World();
	~World();

	private:
	std::vector<Object> objects;
};
