#pragma once
#include<SDL.h>
#include "pixel.h"
#include <exception>
using namespace std;

const Uint32 WHITE = 0xFFFFFF;

class NotOnCanvas : public exception {
	virtual const char* what() noexcept {
		return "The pixel is outside of the canvas surface";
	}
};

class Canvas {

private:
	bool pixel_format_reversed = false;	
	SDL_Renderer *renderer;
	SDL_Surface *backup;
public:
	SDL_Surface *surface;

	Canvas(int width_of_canvas, int height_of_canvas) ;
	~Canvas();
	bool is_on_canvas(Pixel pos);
	bool is_on_canvas(SDL_Rect rect);
	void backup_surface();
	void go_back();
	int get_pixel(Pixel pos);
	void set_pixel(Pixel pos, int colour);
	void fill_at(Pixel pos, int colour);
	void draw_line(Pixel P1, Pixel P2, int color, int width);
	void clear();
	void load_canvas(char* outPath);
	
};


