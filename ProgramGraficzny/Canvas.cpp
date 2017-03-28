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

void Canvas::set_pixel(int x, int y, int pixel)
{
	Uint8 *target_pixel = (Uint8 *)surface->pixels + y * surface->pitch + x*3;
	*(int *)target_pixel = pixel;
}