#pragma once
#include <SDL.h>
#include "pixel.h"
#include "filter.h"
#include <exception>
#include <vector>
using namespace std;

const Uint32 WHITE = 0xFFFFFF;
const int MEMORY_FOR_SAVED_STATES = 300000000;

/*class NotOnCanvas : public exception {
	virtual const char* what() noexcept {
		return "The pixel is outside of the canvas surface";
	}
};*/

class WrongExtension : public exception {
public:
	virtual const char* what() noexcept {
		return "Nieprawidlowe rozszerzenie!\n";
	}
};

class Canvas {

private:
	int rmask;
	int gmask;
	int bmask;

	bool pixel_format_reversed = false;	
	vector<SDL_Surface *> saved_states;
	size_t amount_saved = 0;
public:
	SDL_Surface *surface;

	Canvas(int width_of_canvas, int height_of_canvas) ;
	void init_save_states();
	~Canvas();
	bool is_on_canvas(Pixel pos);
	bool is_on_canvas(SDL_Rect rect);
	void backup_surface();
	void go_back();
	int get_pixel(SDL_Surface* surface, Pixel pos);
	void set_pixel(SDL_Surface* surface, Pixel pos, int colour);
	void fill_at(Pixel pos, int colour);
	void draw_line(Pixel P1, Pixel P2, int color, int width);
	void clear();
	void load_canvas(char* outPath);
	void apply_filter(Filter &filter);	
};


