#include "game.h"

#include "3dsLoader.h"
#include "RawLoader.h"
#include "InputHandler.h"
#include "LevelFactory.h"
#include "Level.h"
#include "world.h"
#include "GLScene.h"
#include "DrawEngine.h"

#include "UI.h"
#include "Logging.h"

#include "Point2d.h"
#include "Point3d.h"

#include "MeshObject.h" /* test hack */

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
CMyGame::CMyGame(World &world, LevelFactory &factory) :
        m_screen(0),
        m_scene(0),
        m_drawEngine(new DrawEngine),
        m_world(world),
        m_levelFactory(factory)
{
    initialize();
}

//destructor
CMyGame::~CMyGame()
{
    // Shutdown all subsystems
    SDL_Quit();

    delete m_drawEngine;
    delete m_scene;
}

// ***methods start

//public
/***********************************************************************
*Desc: method/func for starting the game...
*
*By: Esa Karjalainen, 04. June, 2005
***********************************************************************/
void CMyGame::runGame()
{
    Level *level = m_levelFactory.level(0);
    m_scene->setLevel(level);
    mainLoop();
}


//private
/***********************************************************************
*Desc: game object's initializer routine.
*
*By: Esa Karjalainen, 04. June, 2005
***********************************************************************/

void CMyGame::initialize()
{
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

    screenflags = SDL_OPENGL;

    /* This checks to see if surfaces can be stored in memory */
    if ( videoinfo->hw_available )
    {
        screenflags |= SDL_HWSURFACE;
    }
    else
    {
        screenflags |= SDL_SWSURFACE;
    }

    /* This checks if hardware blits can be done */
    if ( videoinfo->blit_hw )
    {
        screenflags |= SDL_HWACCEL;
    }

    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );

    m_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, screenflags);
    if ( m_screen == NULL ) {
        LOG_ERROR("Unable to set video: %s\n", SDL_GetError());
        exit(1);
    }
    else
    {
        LOG("Screen size h:%d w:%d", m_screen->h, m_screen->w);
    }

    if( !m_drawEngine->initialize() )
    {
        LOG_ERROR("Cannot initialize drawing engine!");
        exit(3);
    }

    // this maybe stupid ::: scene not responsible for videomode.
    m_scene = new GLScene(m_drawEngine);
    m_scene->init();
    m_scene->setup(SCREEN_WIDTH, SCREEN_HEIGHT);
}

/***********************************************************************
*Desc: The game's Main Loop Event
*
*By: Esa Karjalainen, 04. June, 2005
***********************************************************************/

void CMyGame::mainLoop()
{
    enum Actions{LEFT, RIGHT, UP, DOWN, SHOOT, QUIT, ZOOM_IN, ZOOM_OUT, CLEAR};
    unsigned int now = SDL_GetTicks();
    unsigned int ticks = now;
    bool bFlagQuit = false;
    SDL_Event event;

    SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

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
	input->registerAction("clear", CLEAR, SDL_KEYUP, 0);

	m_scene->drawScene(); //don't wait for input to draw the scene
    while ( (SDL_PollEvent(&event) || bFlagQuit == false))
    {
        ticks = SDL_GetTicks() - now;
        if(ticks < 33) 
		{
            SDL_Delay(33-ticks);
        }
        ticks = SDL_GetTicks() - now;
        now += ticks;

        int motion = input->queryEvent(&event);
	

		/*FIXME: hack start*/
		Point3d * location;
		
		MeshObject *meshobj = 0;

		const std::vector<Object*>& objects = m_scene->getLevel()->objects();
		std::vector<Object*>::const_iterator itr = objects.begin();
		std::vector<Object*>::const_iterator itrEnd = objects.end();

		itr = objects.begin();
		for(; itr != itrEnd; itr++)
		{
			MeshObject * tmp = dynamic_cast<MeshObject *>(*itr);
			if(0==tmp->getName().compare("arbyfish")){
				meshobj = tmp;
			}
		}
		
		/*hack end*/
		location = &meshobj->location();
		/*this isn't right - set move direction on keydown, clear on keyup.*/
        switch (motion) {
        case(QUIT):
            bFlagQuit = true;
            break;
        case(UP):
            //m_scene->Camera.location.y -=0.05f;
			location->y-=0.1f;
			meshobj->location(*location);
            break;
        case(DOWN):
            //m_scene->Camera.location.y +=0.05f;
			location->y+=0.1f;
			meshobj->location(*location);
            break;
        case(LEFT):
            //m_scene->Camera.location.x -=0.1f;
			location->x-=0.1f;
			meshobj->location(*location);
            break;
        case(RIGHT):
            //m_scene->Camera.location.x +=0.1f;
			location->x+=0.1f;
			meshobj->location(*location);
            break;
        case(ZOOM_IN):
            m_scene->Camera.location.z +=0.25f;
            break;
        case(ZOOM_OUT):
            m_scene->Camera.location.z -=0.25f;
            break;
        }
		m_drawEngine->renderText(meshobj->getName(), Point2d(5, 5));
		
        m_scene->updateScene(ticks);
        if (motion != -1) {
            m_scene->drawScene();
        }
    }
    delete input;
}

//EOF
