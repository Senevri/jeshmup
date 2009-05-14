#include "game.h"
#include <iostream>
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define SCREEN_BPP 32

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
	Uint32 screenflags = 0;
	const SDL_VideoInfo * videoinfo = NULL;
	// Initialize defaults, Video and Audio 
	Uint32 initflags = SDL_INIT_VIDEO|
		SDL_INIT_AUDIO|
		SDL_INIT_TIMER|
		SDL_INIT_JOYSTICK;
	if((SDL_Init(initflags)==-1)) { 
		printf("Could not initialize SDL: %s.\n", SDL_GetError());
		exit(-1);
	}
	videoinfo = SDL_GetVideoInfo( );

    if( !videoinfo ) {
        /* This should probably never happen. */
        fprintf( stderr, "Video query failed: %s\n",
             SDL_GetError( ) );
		exit(1);
    }

	screenflags =
		SDL_HWPALETTE|
		SDL_OPENGL|
		SDL_GL_DOUBLEBUFFER|
		SDL_ANYFORMAT;

    /* This checks to see if surfaces can be stored in memory */
    if ( videoinfo->hw_available )
	screenflags |= SDL_HWSURFACE;
    else
	screenflags |= SDL_SWSURFACE;

    /* This checks if hardware blits can be done */
    if ( videoinfo->blit_hw )
	screenflags |= SDL_HWACCEL;
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 32 );
    /* Sets up OpenGL double buffering  - redundant w/flag ? */
    //SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
	
	m_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, screenflags);
	if ( m_screen == NULL ) {
		fprintf(stderr, "Unable to set video: %s\n", SDL_GetError());
		exit(1);
	}

	// this maybe stupid ::: scene not responsible for videomode.
	m_scene = new GLScene();
	m_scene->init();
	m_scene->setup(SCREEN_WIDTH, SCREEN_HEIGHT);
	

}
	
/***********************************************************************
*Desc: The game's Main Loop Event
*
*By: Esa Karjalainen, 04. June, 2005
***********************************************************************/

void CMyGame::mainLoop(){

	static int ticks;
	int now = SDL_GetTicks();
	ticks = now + 33;
	bool bFlagQuit = false;
	SDL_Event event;
	
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);	

	setupTestObject();

	while ( (SDL_PollEvent(&event) || bFlagQuit == false)) {
		
		now = SDL_GetTicks();
		if(now>ticks) {
			ticks = now+33; 
		} else {
			SDL_Delay(ticks-now);
		}
	
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
			case SDL_KEYUP :
				break;
			case SDL_USEREVENT :
				break;

			case SDL_QUIT: 
				//	printf("Quit requested, quitting.\n");
				// exit(0);
				bFlagQuit = true;
				break;
		}
		m_scene->drawMesh(0);
		/* draw stuff here */
		SDL_GL_SwapBuffers();
	}

}
	
void CMyGame::setupTestObject(void){
	// copypaste from a blender - outputted .raw file, + regex (s/ /f, /g),
	// and removed the final comma.
		static float obj[] = { 
		1.000000f, 1.000000f, -1.000000f, 1.000000f, -1.000000f, -1.000000f, -1.000000f, -1.000000f, -1.000000f, -1.000000f, 1.000000f, -1.000000f, 
1.000000f, 0.999999f, 1.000000f, -1.000000f, 1.000000f, 1.000000f, -1.000000f, -1.000000f, 1.000000f, 0.999999f, -1.000001f, 1.000000f, 
1.000000f, 1.000000f, -1.000000f, 1.000000f, 0.999999f, 1.000000f, 0.999999f, -1.000001f, 1.000000f, 1.000000f, -1.000000f, -1.000000f, 
1.000000f, -1.000000f, -1.000000f, 0.999999f, -1.000001f, 1.000000f, -1.000000f, -1.000000f, 1.000000f, -1.000000f, -1.000000f, -1.000000f, 
-1.000000f, -1.000000f, -1.000000f, -1.000000f, -1.000000f, 1.000000f, -1.000000f, 1.000000f, 1.000000f, -1.000000f, 1.000000f, -1.000000f, 
1.000000f, 0.999999f, 1.000000f, 1.000000f, 1.000000f, -1.000000f, -1.000000f, 1.000000f, -1.000000f, -1.000000f, 1.000000f, 1.000000
		};
		Mesh *m = new Mesh();
		std::vector<float *> mesh;

		/*6 faces, 4 vertices*/
		m->meshFromFloatArray(obj, Mesh::QUADS, (6*4*3)); /* 6 faces, 4 corners, 3 floats per coord */
		m_scene->addMesh(m);
}

//EOF
