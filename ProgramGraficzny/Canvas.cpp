#include "Canvas.h"
#include <SDL.h>
#include <queue>
#include<SDL_image.h>
#include<iostream>
#include<vector>

using namespace std;

Canvas::Canvas(int width_of_canvas, int height_of_canvas)
{
	rmask = 0x00ff0000;
	gmask = 0x0000ff00;
	bmask = 0x000000ff;
	surface = SDL_CreateRGBSurface(0, width_of_canvas, height_of_canvas, 24, rmask, gmask, bmask, 0);

	SDL_Rect pixel_rect = { 0, 0, 1, 1 };
	SDL_FillRect(surface, &pixel_rect, 0x00ff0000);
	if (get_pixel(Pixel(0, 0)) != 0x00ff0000) {
		SDL_FreeSurface(surface);
		surface = SDL_CreateRGBSurface(0, width_of_canvas, height_of_canvas, 24, 0x000000ff, 0x0000ff00, 0x00ff0000, 0);		
		pixel_format_reversed = true;
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		init_save_states();
	}
	else {
		init_save_states();
	}

	SDL_Rect r = { 0, 0, width_of_canvas, height_of_canvas };
	SDL_FillRect(surface, &r, WHITE);
}

void Canvas::init_save_states() {
	amount_saved = 0;
	int surface_size = surface->w * surface->h * 3;
	saved_states = vector<SDL_Surface *>();
	for (int i = 0; i < MEMORY_FOR_SAVED_STATES; i+= surface_size) {
		saved_states.push_back(SDL_CreateRGBSurface(0, surface->w, surface->h, 24, rmask, gmask, bmask, 0));
	}	
}

Canvas::~Canvas() {
	SDL_FreeSurface(surface);
	for (SDL_Surface* backup : saved_states) {
		SDL_FreeSurface(backup);
	}
}

bool Canvas::is_on_canvas(Pixel pos) {
	
	return pos.x >= 0 && pos.x < surface->w && pos.y >= 0 && pos.y < surface->h;
}

bool Canvas::is_on_canvas(SDL_Rect rect) {
	return rect.x >= 0 && rect.y >= 0 && rect.x + rect.w <= surface->w && rect.y + rect.h <= surface->h;
}

void Canvas::backup_surface() {
	amount_saved += 1;
	if (amount_saved > saved_states.size()) {
		amount_saved = saved_states.size();
	}
	SDL_Rect r = { 0, 0, surface->w, surface->h };
	SDL_Surface* last = saved_states[0];
	for (int i = 1; i < saved_states.size(); i++) 
	{		
		saved_states[i - 1] = saved_states[i];
	}	
	SDL_BlitSurface(surface, &r, last, &r);
	saved_states[saved_states.size() - 1] = last;	
}

void Canvas::go_back() {
	if (amount_saved == 0) {
		return;
	}
	amount_saved -= 1;

	SDL_Surface* first = saved_states[saved_states.size() - 1];
	SDL_Rect r = { 0, 0, surface->w, surface->h };
	SDL_BlitSurface(first, &r, surface, &r);
	
	for (size_t i = saved_states.size() - 1; i > 0; i--) {
		saved_states[i] = saved_states[i - 1];
	}
	saved_states[0] = first;
}

int Canvas::get_pixel(Pixel pos) {
	if (!is_on_canvas(pos)) {

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
		//throw NotOnCanvas();
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
		SDL_Rect rect = { P1.x, P1.y, width, width };
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
		SDL_Rect rect = { (int)x, (int)y, width, width };
		if (is_on_canvas(rect)) {
			SDL_FillRect(surface, &rect, colour);
		}
		x += addx;
		y += addy;
	}

}
void Canvas::clear()
{
	backup_surface();
	SDL_Rect rect = { 0, 0,surface->w, surface->h };
	SDL_FillRect(surface, &rect, 0xFFFFFF);

}
void Canvas::load_canvas(char* outPath)
{
	SDL_FreeSurface(surface);
	for (SDL_Surface* backup_surface : saved_states) {
		SDL_FreeSurface(backup_surface);
	}
	surface = IMG_Load(outPath);	
	init_save_states();
	cout << surface->w << endl;
}