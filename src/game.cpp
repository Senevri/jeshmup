#include "game.h"
#include <iostream>

//constructor, destructor

/***********************************************************************
*Desc: The game encapsulated as a class.
*
*By: Esa Karjalainen, 04. June, 2005
***********************************************************************/
CMyGame::CMyGame(){	
	initialize();
}

//destructor
CMyGame::~CMyGame(){	
	// Shutdown all subsystems 
	SDL_Quit();	
	exit(0);
}

// ***methods start

//public
/***********************************************************************
*Desc: method/func for starting the game...
*
*By: Esa Karjalainen, 04. June, 2005
***********************************************************************/
void CMyGame::runGame(){	
	//the one, the only....
	mainLoop();
}


//private
/***********************************************************************
*Desc: game object's initializer routine.
*
*By: Esa Karjalainen, 04. June, 2005
***********************************************************************/

void CMyGame::initialize(){
		
	// Initialize defaults, Video and Audio 
	if((SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER)==-1)) { 
		printf("Could not initialize SDL: %s.\n", SDL_GetError());
		exit(-1);
	}
	

	//SDL_Surface *screen;
	
	m_screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE|SDL_ANYFORMAT);
	if ( m_screen == NULL ) {
		fprintf(stderr, "Unable to set 640x480 video: %s\n", SDL_GetError());
		myWaitEvent();
		exit(1);
	}
 
}
	
/***********************************************************************
*Desc: The game's Main Loop Event
*
*By: Esa Karjalainen, 04. June, 2005
***********************************************************************/

void CMyGame::mainLoop(){

	bool bFlagQuit = false;
	SDL_Event event;
	while ( (SDL_WaitEvent(&event) >= 0) && (bFlagQuit == false)) {
		switch (event.type) {			
			case SDL_KEYDOWN: 
				switch( event.key.keysym.sym ){				
					case SDLK_ESCAPE:
						bFlagQuit = true;
						break;					
					default:
						break;
				}
				break;						
			case SDL_QUIT: 
			//	printf("Quit requested, quitting.\n");
			// exit(0);
			bFlagQuit = true;
			break;
		}
	}
}
	
	
//I think this is junk...
void CMyGame::myWaitEvent(){
	SDL_Event event;
	SDL_WaitEvent(&event);
	switch (event.type) {
		case SDL_KEYDOWN:
			printf("The %s key was pressed!\n",
				   SDL_GetKeyName(event.key.keysym.sym));
			break;
		case SDL_QUIT:
			exit(0);
			break;
		default:
			break;	
	}
}

//EOF
