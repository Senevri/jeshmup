#include <iostream>
#include "SDL.h"
#include "UnitTest++.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define SCREEN_BITS 16

int init_screen(void);

int main( int argc, char *argv[] )
{
	init_screen();

	if(SDL_Init(SDL_INIT_VIDEO) <0){
		std::cout<<"Could not init SDL:"<<SDL_GetError()<<"\n";
		exit(1);
	}
	SDL_Quit();
	return 0;
}


// does nothing, reserve screen elsewhere, idiot!
int init_screen(void)
{
	SDL_Surface *screen = NULL ;
	SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BITS, SDL_ANYFORMAT);
	return 0;
}

