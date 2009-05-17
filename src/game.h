/**
 *	game.h 
 *	
 *	by: Esa Karjalainen
 *	has: main loop
 */

#pragma once 
#include "SDL.h"
#include "GLScene.h"

class CMyGame{

public:
	//constructor, destructor
	CMyGame();
	~CMyGame();

	//methods
	void runGame();

private:
	
	SDL_Surface *m_screen;
	GLScene * m_scene;
	void initialize();
	void myWaitEvent();
	void mainLoop();

	//test
	void setupTestObject(void);

};
