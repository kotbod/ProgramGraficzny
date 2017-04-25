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
	bool is_on_canvas(Pixel pos);
	int get_pixel(Pixel pos);
	void set_pixel(Pixel pos, int colour);
	void fill_at(Pixel pos, int colour);
	void draw_line(Pixel P1, Pixel P2, int color, int width);
	void clear();
	void load_canvas(char* outPath);
	
};


