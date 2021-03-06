/*
 * InputHandler.h
 * by: Esa Karjalainen
 * has: InputHandler class abstracting user input somewhat.
 */

#ifndef _INPUTHANDLER_H_
#define _INPUTHANDLER_H_

#include <iostream>
#include <string>
#include <vector>
#include <SDL.h>

class InputHandler
{
public:
	InputHandler(void);
	~InputHandler(void);
	/* add a potential action to look out for */
	void registerAction(const std::string name, unsigned int id, unsigned char sdl_event_type, Uint16 value);
	int queryEvent(const SDL_Event *event); /* returns ID of event. */
	std::string queryEventName(unsigned int id);	
	enum joy_motion {JOYUP, JOYDOWN, JOYLEFT, JOYRIGHT};

private:
	typedef struct{
		std::string name;
		unsigned int id;
		unsigned char sdl_event_type;
		Uint16 value;
	} action;
	std::vector<action> actions;
	SDL_Joystick * m_pjoystick;
};

#endif //_INPUTHANDLER_H_
