#include "Canvas.h"
#include <SDL.h>

struct Colour {
	Uint8 red;
	Uint8 green;
	Uint8 blue;
};

Canvas::Canvas(int width_of_canvas, int height_of_canvas)
{
	surface = SDL_CreateRGBSurface(0, width_of_canvas, height_of_canvas, 24,0x00000FF,0x0000FF00,0x00FF0000,0);
	SDL_Rect r = { 0, 0, width_of_canvas, height_of_canvas };
	SDL_FillRect(surface, &r, WHITE);

}

Canvas::~Canvas() {
	SDL_FreeSurface(surface);
}

void Canvas::set_pixel(Pixel pos, int colour)
{
	SDL_LockSurface(surface);
	Uint8 *target_pixel = (Uint8 *)surface->pixels + pos.y * surface->pitch + pos.x * 3;
	Colour *target = (Colour *)target_pixel;
	Colour our_colour;
	our_colour.red  = (Uint8)(colour >> 16);
	our_colour.green = (Uint8)(colour >> 8);
	our_colour.blue = (Uint8)(colour >> 0);

	*target = our_colour;
	SDL_UnlockSurface(surface);
}
void Canvas::draw_line(Pixel P1, Pixel P2, int colour) {
	double x = P2.x - P1.x;
	double y = P2.y - P1.y;
	double length = sqrt(x*x + y*y);

	if (length < 1)
	{
		set_pixel(P1, colour);
		return; 

	}

	double addx = x / length;//wektor kierunkowy 
	double addy = y / length;

	x = P1.x;
	y = P1.y;

	for (double i = 0; i < length; i += 1)
	{
		set_pixel(Pixel((int)x, (int)y),colour);
		x += addx;
		y += addy;
	}

}