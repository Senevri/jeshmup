#include "InputHandler.h"

InputHandler::InputHandler(void)
{
	SDL_JoystickEventState(SDL_ENABLE);
	this->m_pjoystick = SDL_JoystickOpen(0);
}

InputHandler::~InputHandler(void)
{
}

/* registerAction:
 * name: some name we wanna call it
 * id: id we recognize this action as - typically enumerated.
 * sdl_event_type: from SDL_Event.type
 * value: a specific char / button / data we expect
 */
void InputHandler::registerAction(const std::string name, 
								 unsigned int id, 
								 unsigned char sdl_event_type, 
								 Uint16 value)
{
	action a;
	a.id = id;
	a.name = name;
	a.sdl_event_type = sdl_event_type;
	a.value = value;
	this->actions.push_back(a);
}

/*TODO: IN PROGRESS!!!1one*/
int InputHandler::queryEvent(const SDL_Event *event){
	std::vector<action>::iterator itr;
	for ( itr = this->actions.begin(); itr < this->actions.end(); ++itr ){
		if(event->type == itr->sdl_event_type){
			switch(event->type){
			case SDL_KEYUP:
				if(itr->value==event->key.keysym.sym)
					return itr->id;
				break;
			case SDL_KEYDOWN:
				if(itr->value==event->key.keysym.sym)
					return itr->id;
				break;
			case SDL_MOUSEMOTION:
				break;
			case SDL_MOUSEBUTTONUP:
				break;
			case SDL_MOUSEBUTTONDOWN:
				break;
			case SDL_JOYBUTTONUP:
				break;
			case SDL_JOYBUTTONDOWN:
				if(itr->value==event->jbutton.button)
					return itr->id;
				break;
			case SDL_JOYAXISMOTION:
				if(itr->value==event->jaxis.axis)
					return ( itr->id );
				break;
			case SDL_JOYBALLMOTION:
				break;
			case SDL_JOYHATMOTION:
				break;
			default:
				return itr->id;
			}
		} //if
	}//for
	return -1;  /* no action found */
}
