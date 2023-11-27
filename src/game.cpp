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
#include <sstream>
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define SCREEN_BPP 32

//constructor, destructor

/***********************************************************************
*Desc: The game encapsulated as a class.
*
*By: Esa Karjalainen, 04. June, 2005
***********************************************************************/
MyGame::MyGame(World &world, LevelFactory &factory) :
		m_screen(0),
		m_scene(0),
		m_drawEngine(new DrawEngine),
		m_world(world),
		m_levelFactory(factory)
{
	initialize();
}

//destructor
MyGame::~MyGame()
{
	// Shutdown all subsystems
	// TODO: Wrap all SDL stuff.
	sys_quit();

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
void MyGame::runGame()
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

void MyGame::initialize()
{
	
	Uint32 screenflags = sys_initvideo();
	

	m_screen = sys_setvideomode(SCREEN_WIDTH, SCREEN_HEIGHT, screenflags);
		
		
	if ( m_screen == NULL ) {
		LOG_ERROR("Unable to set video: %s\n", sys_get_error_string());
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
* TODO: Wrap SDL calls
*By: Esa Karjalainen, 04. June, 2005
***********************************************************************/

void MyGame::mainLoop()
{
	enum Actions{LEFT, RIGHT, UP, DOWN, SHOOT, QUIT, ZOOM_IN, ZOOM_OUT, CLEAR};
	unsigned int now = SDL_GetTicks();
	unsigned int ticks = now;
	bool bFlagQuit = false;
	int angle=0;
	signed int a=4;
	signed int b=0;

	SDL_Event event;
	Point2d player_motion;
	SDLKey k;

	SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL);

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
	input->registerAction("clear", CLEAR, SDL_KEYUP, SDLK_LEFT);
	input->registerAction("clear", CLEAR, SDL_KEYUP, SDLK_RIGHT);
	input->registerAction("clear", CLEAR, SDL_KEYUP, SDLK_UP);
	input->registerAction("clear", CLEAR, SDL_KEYUP, SDLK_DOWN);

	m_scene->drawScene(); //don't wait for input to draw the scene
	
	while ( (SDL_PollEvent(&event) || bFlagQuit == false))
	{
		ticks = SDL_GetTicks() - now;
		if(ticks < 40) 
		{
			SDL_Delay(40-ticks);
		}
		ticks = SDL_GetTicks() - now;
		now += ticks;

		int motion = input->queryEvent(&event);
		k=event.key.keysym.sym;

		/*FIXME: hack start*/
		Point3d location;
		
		MeshObject * meshobj[2] = {0,0};

		const std::vector<Object*>& objects = m_scene->getLevel()->objects();		
		std::vector<Object*>::const_iterator itr = objects.begin();
		std::vector<Object*>::const_iterator itrEnd = objects.end();

		itr = objects.begin();
		for(; itr != itrEnd; itr++)
		{
			MeshObject * tmp = dynamic_cast<MeshObject *>(*itr);
			int val = tmp->getName().compare("shippi");
			if(0==val){
			    meshobj[0] = tmp;
			} else {
			    int val = tmp->getName().compare("blendertest");
			    if(0==val){
				meshobj[1] = tmp;
			    }
			}
		}
		
		if( meshobj[0] )
		{
			location = meshobj[0]->location();
		}
		/*hack end*/

		/*this isn't right - set move direction on keydown, clear on keyup.*/
		switch (motion) {
		case(QUIT):
			bFlagQuit = true;
			break;
		case(UP):
			player_motion.y=-0.1f;
			break;
		case(DOWN):
			player_motion.y=0.1f;
			break;
		case(LEFT):
			player_motion.x=-0.1f;
			break;
		case(RIGHT):
			player_motion.x=0.1f;
			break;
		case(CLEAR):			
			if (k==SDLK_LEFT ||k==SDLK_RIGHT){
				player_motion.x=0;
			} 
			if (k==SDLK_UP ||k==SDLK_DOWN){
				player_motion.y=0;
			}			
			break;
		case(ZOOM_IN):
			m_scene->Camera.location.z +=0.25f;
			break;
		case(ZOOM_OUT):
			m_scene->Camera.location.z -=0.25f;
			break;
		}
		location.x += player_motion.x;
		location.y += player_motion.y;
		if( meshobj[1] )
		{			
			meshobj[0]->location(location);
			meshobj[0]->rotation(angle, Point3d(0, 1, 0));
			angle=angle+a;
			if(a==4 && angle>40) {
			   //angle=40;
			   a=-4;
			}
			if(a==-4 && angle<-40) {
			    //angle=-39
			    a=4;
			}
			meshobj[1]->rotation(b, Point3d(1, 1, 1));
			b++;
			if (b>355) {
			    b=0;
			}
		}
		std::ostringstream os;
		os << "FPS:" << (1000/ticks);
		std::string rq(os.str());
		UI::instance()->requestWrite(rq);
		m_scene->updateScene(ticks);
		//if (motion != -1) {
			m_scene->drawScene();
		//}

	}
	delete input;
}

//EOF
