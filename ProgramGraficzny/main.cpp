#include <SDL.h>


#include "application.h"

int main(int argc, char **argv) {
	SDL_Init(SDL_INIT_EVERYTHING);
	
	{
		Application app;
		app.start();
	}
	
	SDL_Quit();
	return 0;
}