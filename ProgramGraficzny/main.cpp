#include <SDL.h>
#include <SDL_ttf.h>

#include "application.h"

int main(int argc, char **argv) {
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	{
		Application app;
		app.start();
	}
	TTF_Quit();
	SDL_Quit();

	return 0;
}