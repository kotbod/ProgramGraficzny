#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "pixel.h"
#include "filter.h"
#include <vector>
#include <string>

using namespace std;

class WrongExtension : public exception {
public:
	virtual const char* what() noexcept {
		return "Nieprawidlowe rozszerzenie!\n";
	}
};

class Surface {
private:
	

	int rmask;
	int gmask;
	int bmask;

	bool pixel_format_reversed = false;

	void create();
public:
	SDL_Surface* _surface;
	int width;
	int height;
	SDL_Rect rect;

	Surface(int width, int height);	
	Surface(string pathname);
	Surface(Surface &other);
	~Surface();
	
	bool contains(Pixel pos);
	bool contains(SDL_Rect rect);	
	
	int get_pixel(Pixel pos);
	void set_pixel(Pixel pos, int colour);
	void fill_rectangle(SDL_Rect *rect, int colour);
	void blit(Surface* surface, SDL_Rect *rect);
	Surface *with_filter(Filter &with_filter);
	Surface *as_grayscale();
	Surface *blend(Surface * other, SDL_Rect * dest);

	void save(string pathname);
};


