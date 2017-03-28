#include "Canvas.h"
#include <SDL.h>

Canvas::Canvas(int width_of_canvas, int height_of_canvas)
{
	surface = SDL_CreateRGBSurface(0, width_of_canvas, height_of_canvas, 24,0,0,0,0);
	SDL_Rect r = { 0, 0, width_of_canvas, height_of_canvas };
	SDL_FillRect(surface, &r, WHITE);

}

Canvas::~Canvas() {
	SDL_FreeSurface(surface);
}

void Canvas::set_pixel(Pixel pos, int color)
{
	Uint8 *target_pixel = (Uint8 *)surface->pixels + pos.y * surface->pitch + pos.x*3;
	*(int *)target_pixel = color;
}
void Canvas::draw_line(Pixel P1, Pixel P2, int color) {

	double x = P1.x - P2.x;
	double y = P1.y - P2.y;
	double length = sqrt(x*x + y*y);

	if (length < 1)
	{
		set_pixel(P1, color);
		return; 

	}

	double addx = x / length;//wektor kierunkowy 
	double addy = y / length;

	x = P1.x;
	y = P1.y;

	for (double i = 0; i < length; i += 1)
	{
		set_pixel(Pixel((int)x, (int)y),color);
		x += addx;
		y += addy;
	}

}