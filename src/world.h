
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

	typedef struct {
		float x;
		float y;
		float z;
	} coordinate;

	World();
	~World();

	private:
		/* object-in-world, world-object -> wob */
		typedef struct {
			Object object;
			coordinate location;
			coordinate facing; /* (effectively a vector) */
			coordinate velocity; /* motion vector */
		}actor;
		std::vector<actor> actors;
};
