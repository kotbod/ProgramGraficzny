#include "Canvas.h"
#include <SDL.h>
#include <queue>
#include<SDL_image.h>
#include<iostream>


using namespace std;

Canvas::Canvas(int width_of_canvas, int height_of_canvas)
{
	int rmask, gmask, bmask, amask;
	//if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
		rmask = 0x00ff0000;
		gmask = 0x0000ff00;
		bmask = 0x000000ff;
	//}
	//else {
		//rmask = 0x000000ff;
		//gmask = 0x0000ff00;
		//bmask = 0x00ff0000;
	//}
	amask = 0;

	surface = SDL_CreateRGBSurface(0, width_of_canvas, height_of_canvas, 24,rmask,gmask,bmask,0);
	SDL_Rect r = { 0, 0, width_of_canvas, height_of_canvas };
	SDL_FillRect(surface, &r, WHITE);

}

Canvas::~Canvas() {
	SDL_FreeSurface(surface);
}

bool Canvas::is_on_canvas(Pixel pos) {
	
	return pos.x >= 0 && pos.x < surface->w && pos.y >= 0 && pos.y < surface->h;
}

int Canvas::get_pixel(Pixel pos) {
	Uint8 *p = (Uint8 *)surface->pixels + pos.y * surface->pitch + pos.x * 3;
	return p[2] << 16 | p[1] << 8 | p[0];	
}

void Canvas::set_pixel(Pixel pos, int colour)
{
	SDL_Rect pixel_rect = { pos.x, pos.y, 1, 1 };
	SDL_FillRect(surface, &pixel_rect, colour);		
}

void Canvas::fill_at(Pixel pos, int colour)
{
	if (!is_on_canvas(pos) || get_pixel(pos) == colour) {
		return;
	}
	SDL_LockSurface(surface);
	int original_colour = get_pixel(pos);
	
	vector<Pixel> stack;
	stack.push_back(pos);
	while (stack.size() > 0) {
		Pixel next = stack[stack.size() - 1];
		stack.pop_back();
		Pixel directions[4] = { Pixel(0, 1), Pixel(1, 0), Pixel(-1, 0), Pixel(0, -1) };
		for (Pixel p : directions) {
			if (is_on_canvas(next + p) && get_pixel(next + p) == original_colour) {
				set_pixel(next + p, colour);
				stack.push_back(next + p);
			}
		}		
	}
	SDL_UnlockSurface(surface);

}

void Canvas::draw_line(Pixel P1, Pixel P2, int colour, int width) {
	double x = P2.x - P1.x;
	double y = P2.y - P1.y;
	double length = sqrt(x*x + y*y);


	if (length < 1)
	{
		SDL_Rect rect = { x, y, width, width };
		SDL_FillRect(surface, &rect, colour);
		set_pixel(P1, colour);
		return; 

	}

	double addx = x / length;//wektor kierunkowy 
	double addy = y / length;

	x = P1.x;
	y = P1.y;

	for (double i = 0; i < length; i += 1)
	{
		SDL_Rect rect = { x, y, width, width };
		SDL_FillRect(surface, &rect, colour);
		x += addx;
		y += addy;
	}

}
void Canvas::clear()
{
	SDL_Rect rect = { 0, 0,surface->w, surface->h };
	SDL_FillRect(surface, &rect, 0xFFFFFF);

}
void Canvas::load_canvas(char* outPath)
{
	SDL_FreeSurface(surface);
	surface = IMG_Load(outPath);
	cout << surface->w << endl;
}