
/**
 * ZA WARUDO: 
 * Contains a list of objects and their locations, and so on...
 *  - Object statuses?
 *  - functions for manipulating, loading, saving, etc. of the world
 **/
#include "object.h"
#include <vector>
#include <string>

class World {
	public:

	typedef struct {
		float x;
		float y;
		float z;
	} coordinate;

	World();
	~World();

	unsigned int createActor(std::string name); /* returnvalue ID */
	bool createActor(std::string name, unsigned int id);
	bool setActorLocation(unsigned int id, float x, float y, float z);
	bool setActorFacing(unsigned int id, float x, float y, float z);
	bool setActorVelocity(unsigned int id, float x, float y, float z);
	bool moveActorForward(unsigned int id, float amount);
	bool moveActorSideways(unsigned int id, float amount);
	bool moveActorVertically(unsigned int id, float amount);

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
