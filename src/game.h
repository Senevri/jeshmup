/**
 *	game.h 
 *	
 *	by: Esa Karjalainen
 *	has: main loop
 */

#ifndef _GAME_H_
#define _GAME_H_


#include "system.h"

class LevelFactory;
class GLScene;
class DrawEngine;
class World;
//class SDL_Surface;

class MyGame{

public:
	//constructor, destructor
    MyGame(World &world, LevelFactory &factory);
	~MyGame();

	//methods
	void runGame();

private:
    void initialize();
    char* initSystem(SURFACE **screen);
    void myWaitEvent();
    void mainLoop();
    void setupTestObject();

private: //data
	SURFACE *m_screen;
    GLScene *m_scene;
    DrawEngine *m_drawEngine;

    World &m_world;
    LevelFactory &m_levelFactory;
};

#endif //_GAME_H_
