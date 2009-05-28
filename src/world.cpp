/** ZA WARUDO implementations 
 **/
#include "world.h"

World::World() {
}

World::~World(){
}

/* creates an actor and returns it's ID. 
 */
unsigned int World::createActor(std::string name)
{
	return -1;
}

/**
 * creates an actor, returvalue nonsense
 */
bool World::createActor(std::string name, unsigned int id)
{
	return false;
}

/** 
 * teleports the actor to a specific location in the world
 */
bool World::setActorLocation(unsigned int id, float x, float y, float z){
	return false;
}

/**
 *	rotate actor in polar coords
 */
bool World::setActorFacing(unsigned int id, float x, float y, float z){
	return false;
}

/**
 * motion vector?
 * 
 */
bool World::setActorVelocity(unsigned int id, float x, float y, float z){

	return false;
}

/**
 * the following functions move an actor according to their 
 * personal position - IE, in relation to their facing.
 * Maybe they manipulate velocity vector?
 */

bool World::moveActorForward(unsigned int id, float amount){
	return false;
}
bool World::moveActorSideways(unsigned int id, float amount){
	return false;
}
bool World::moveActorVertically(unsigned int id, float amount){
	return false;
}
