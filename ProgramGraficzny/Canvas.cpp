#include "Canvas.h"
#include <SDL.h>
#include <queue>
#include<SDL_image.h>
#include<iostream>


using namespace std;

Canvas::Canvas(int width_of_canvas, int height_of_canvas)
{
	surface = SDL_CreateRGBSurface(0, width_of_canvas, height_of_canvas, 24, 0x00ff0000, 0x0000ff00, 0x000000ff, 0);

	SDL_Rect pixel_rect = { 0, 0, 1, 1 };
	SDL_FillRect(surface, &pixel_rect, 0x00ff0000);
	if (get_pixel(Pixel(0, 0)) != 0x00ff0000) {
		SDL_FreeSurface(surface);
		surface = SDL_CreateRGBSurface(0, width_of_canvas, height_of_canvas, 24, 0x000000ff, 0x0000ff00, 0x00ff0000, 0);
		backup = SDL_CreateRGBSurface(0, width_of_canvas, height_of_canvas, 24, 0x000000ff, 0x0000ff00, 0x00ff0000, 0);
		pixel_format_reversed = true;
	}
	else {
		backup = SDL_CreateRGBSurface(0, width_of_canvas, height_of_canvas, 24, 0x00ff0000, 0x0000ff00, 0x000000ff, 0);
	}

	SDL_Rect r = { 0, 0, width_of_canvas, height_of_canvas };
	SDL_FillRect(surface, &r, WHITE);
	SDL_FillRect(backup, &r, WHITE);
}

Canvas::~Canvas() {
	SDL_FreeSurface(surface);
}

bool Canvas::is_on_canvas(Pixel pos) {
	
	return pos.x >= 0 && pos.x < surface->w && pos.y >= 0 && pos.y < surface->h;
}

bool Canvas::is_on_canvas(SDL_Rect rect) {
	return rect.x >= 0 && rect.y >= 0 && rect.x + rect.w <= surface->w && rect.y + rect.h <= surface->h;
}

void Canvas::backup_surface() {
	SDL_Rect r = { 0, 0, surface->w, surface->h };
	SDL_BlitSurface(surface, &r, backup, &r);
}

void Canvas::go_back() {
	SDL_Rect r = { 0, 0, surface->w, surface->h };
	SDL_BlitSurface(backup, &r, surface, &r);
}

int Canvas::get_pixel(Pixel pos) {
	if (!is_on_canvas(pos)) {
		throw NotOnCanvas();
	}
	Uint8 *p = (Uint8 *)surface->pixels + pos.y * surface->pitch + pos.x * 3;
	if (pixel_format_reversed) {
		return p[0] << 16 | p[1] << 8 | p[2];
	}
	else {
		return p[2] << 16 | p[1] << 8 | p[0];
		
	}	
}

void Canvas::set_pixel(Pixel pos, int colour)
{
	if (!is_on_canvas(pos)) {
		throw NotOnCanvas();
	}
	Uint8 *p = (Uint8 *)surface->pixels + pos.y * surface->pitch + pos.x * 3;
	if (pixel_format_reversed) {
		p[0] = colour >> 16;
		p[1] = colour >> 8;
		p[2] = colour >> 0;
	}
	else {
		p[0] = colour >> 0;
		p[1] = colour >> 8;
		p[2] = colour >> 16;
	}	
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
		if (is_on_canvas(rect)) {
			SDL_FillRect(surface, &rect, colour);
		}		
		return; 

	}

	double addx = x / length;//wektor kierunkowy 
	double addy = y / length;

	x = P1.x;
	y = P1.y;

	for (double i = 0; i < length; i += 1)
	{
		SDL_Rect rect = { x, y, width, width };
		if (is_on_canvas(rect)) {
			SDL_FillRect(surface, &rect, colour);
		}
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
	SDL_FreeSurface(backup);
	surface = IMG_Load(outPath);	
	backup = IMG_Load(outPath);	
	cout << surface->w << endl;
}