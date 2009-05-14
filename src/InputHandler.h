#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "SDL.h"

class InputHandler
{
public:
	InputHandler(void);
	~InputHandler(void);
	/* add a potential action to look out for */
	int registerAction(const std::string name, unsigned int id, unsigned char sdl_event_type);
	int queryEvent(const SDL_Event *event); /* returns ID of event. */
	std::string queryEventName(unsigned int id);
private:
	typedef struct{
		std::string name;
		unsigned int id;
		unsigned char sdl_event_type;
	} action;
	std::vector<action *> actions;
};
