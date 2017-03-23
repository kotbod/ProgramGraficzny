#pragma once
#include<SDL.h>

const Uint32 WHITE = 0xFFFFFF;

class Canvas {

public:
	SDL_Surface *surface;
	

public:
	Canvas(int width_of_canvas, int height_of_canvas) ;
	~Canvas();
	
};
