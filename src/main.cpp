#include <iostream>
#include "SDL.h"

int main( int argc, char *argv[] )
{
	if(SDL_Init(0) <0){
		std::cout<<"Could not init SDL:"<<SDL_GetError()<<"\n";
		exit(1);
	}	
	SDL_Quit();
	return 0;
}
