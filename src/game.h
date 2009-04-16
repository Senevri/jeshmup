#pragma once 
#include "sdl.h"

class CMyGame{

public:
	//constructor, destructor
	CMyGame();
	~CMyGame();

	//methods
	void runGame();


private:
	
	SDL_Surface *m_screen;
	void initialize();
	void myWaitEvent();
	void mainLoop();

};
