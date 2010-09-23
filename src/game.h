/**
 *	game.h 
 *	
 *	by: Esa Karjalainen
 *	has: main loop
 */

#ifndef _GAME_H_
#define _GAME_H_

#include <SDL/SDL.h>

class LevelFactory;
class GLScene;
class DrawEngine;
class World;

class CMyGame{

public:
	//constructor, destructor
    CMyGame(World &world, LevelFactory &factory);
	~CMyGame();

	//methods
	void runGame();

private:
    void initialize();
    void myWaitEvent();
    void mainLoop();
    void setupTestObject();

private: //data
	SDL_Surface *m_screen;
    GLScene *m_scene;
    DrawEngine *m_drawEngine;

    World &m_world;
    LevelFactory &m_levelFactory;
};

#endif //_GAME_H_
