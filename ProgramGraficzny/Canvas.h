#pragma once
#include<SDL.h>
#include "pixel.h"

const Uint32 WHITE = 0xFFFFFF;

class Canvas {

public:
	SDL_Surface *surface;
	SDL_Renderer *renderer;

public:
	Canvas(int width_of_canvas, int height_of_canvas) ;
	~Canvas();
	void set_pixel(Pixel pos, int color);
	void draw_line(Pixel P1, Pixel P2, int color);
};


