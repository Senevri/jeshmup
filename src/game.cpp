#include "game.h"

#include "util/RawLoader.h"
#include "InputHandler.h"
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
	this->m_world = new World();
	mainLoop();
	delete this->m_world;
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

	enum actions{LEFT, RIGHT, UP, DOWN, SHOOT, QUIT, ZOOM_IN, ZOOM_OUT};
	static int ticks;
	int now = SDL_GetTicks();
	ticks = now + 33;
	bool bFlagQuit = false;
	SDL_Event event;
	
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);	

	/* TEST */
	setupTestObject();

	this->m_world->setActorLocation(0, 10, 10, 10);
	/* END TEST */
	InputHandler * input = new InputHandler();
	input->registerAction("quit", QUIT, SDL_QUIT, 0);
	input->registerAction("quit_esc", QUIT, SDL_KEYDOWN, SDLK_ESCAPE);
	input->registerAction("up", UP, SDL_KEYDOWN, SDLK_UP);
	input->registerAction("down", DOWN, SDL_KEYDOWN, SDLK_DOWN);
	input->registerAction("left", LEFT, SDL_KEYDOWN, SDLK_LEFT);
	input->registerAction("right", RIGHT, SDL_KEYDOWN, SDLK_RIGHT);
	input->registerAction("in", ZOOM_IN, SDL_KEYDOWN, SDLK_PAGEUP);
	input->registerAction("out", ZOOM_OUT, SDL_KEYDOWN, SDLK_PAGEDOWN);
	input->registerAction("joy_up", UP, SDL_JOYAXISMOTION, input->JOYUP);
	input->registerAction("joy_down", DOWN, SDL_JOYAXISMOTION, input->JOYDOWN);
	input->registerAction("joy_left", LEFT, SDL_JOYAXISMOTION, input->JOYLEFT);
	input->registerAction("joy_right", RIGHT, SDL_JOYAXISMOTION, input->JOYRIGHT);
	

	while ( (SDL_PollEvent(&event) || bFlagQuit == false)) {
		
		now = SDL_GetTicks();
		if(now>ticks) {
			ticks = now+33; 
		} else {
			SDL_Delay(ticks-now);
		}
	
		int motion = input->queryEvent(&event);		
		
		switch (motion) {						
			case(QUIT):
				bFlagQuit = true;
				break;
			case(UP):
				m_scene->camera.location.y -=0.01f;
				break;
			case(DOWN):
				m_scene->camera.location.y +=0.01f;
				break;
			case(LEFT):
				m_scene->camera.location.x -=0.02f;
				break;
			case(RIGHT):
				m_scene->camera.location.x +=0.02f;
				break;
			case(ZOOM_IN):
				m_scene->camera.location.z +=0.05f;
				break;
			case(ZOOM_OUT):
				m_scene->camera.location.z -=0.05f;
				break;
		}    
		m_scene->drawScene();
		//glTranslate
		
		/* draw stuff here */
		SDL_GL_SwapBuffers();
	}
	delete input;

}
	
void CMyGame::setupTestObject(void){
		RawLoader *r = new RawLoader();
		r->load("..\\data\\model\\Arby_whole.raw");
		Mesh *m1 = new Mesh(r->getVertices(), Mesh::TRIANGLES);
		m_scene->addMesh(m1);
		delete r;
		//r = new RawLoader();
		//r->load("..\\data\\model\\Arby_head.raw");
		//Mesh *m2 = new Mesh(r->getVertices(), Mesh::TRIANGLES);
		//m_scene->addMesh(m2);
		//delete r;
		//r = new RawLoader();
		//r->load("..\\data\\model\\Arby_back.raw");
		//Mesh *m3 = new Mesh(r->getVertices(), Mesh::TRIANGLES);
		//m_scene->addMesh(m3);
		//delete r;		
}

//EOF
