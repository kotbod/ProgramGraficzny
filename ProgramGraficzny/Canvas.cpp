#include "Canvas.h"
#include <SDL.h>
#include <queue>
#include<SDL_image.h>
#include<iostream>
#include<vector>

using namespace std;

Canvas::Canvas(int width, int height)
{
	surface = new Surface(width, height);
	init_save_states();
	clear();
}

void Canvas::init_save_states() {
	amount_saved = 0;
	int surface_bytes = surface->width * surface->height * 3;
	saved_states = vector<Surface *>();
	for (int i = 0; i < MEMORY_FOR_SAVED_STATES; i+= surface_bytes) {
		saved_states.push_back(new Surface(surface->width, surface->height));
	}	
}

Canvas::~Canvas() {
	delete surface;
	for (Surface *backup_surface : saved_states) {
		delete backup_surface;
	}
}

void Canvas::backup_surface() {
	amount_saved += 1;
	if (amount_saved > saved_states.size()) {
		amount_saved = saved_states.size();
	}
	SDL_Rect r = { 0, 0, surface->width, surface->height };
	Surface *last = saved_states[0];
	for (int i = 1; i < saved_states.size(); i++) 
	{		
		saved_states[i - 1] = saved_states[i];
	}	
	last->blit(surface, &r);	
	saved_states[saved_states.size() - 1] = last;	
}

void Canvas::go_back() {
	if (amount_saved == 0) {
		return;
	}
	amount_saved -= 1;

	Surface* first = saved_states[saved_states.size() - 1];
	SDL_Rect r = { 0, 0, surface->width, surface->height };
	surface->blit(first, &r);	
	
	for (size_t i = saved_states.size() - 1; i > 0; i--) {
		saved_states[i] = saved_states[i - 1];
	}
	saved_states[0] = first;
}

void Canvas::fill_at(Pixel pos, int colour)
{
	if (!surface->contains(pos) || surface->get_pixel(pos) == colour) {
		return;
	}	
	int original_colour = surface->get_pixel(pos);
	
	vector<Pixel> stack;
	stack.push_back(pos);
	while (stack.size() > 0) {
		Pixel next = stack[stack.size() - 1];
		stack.pop_back();
		Pixel directions[4] = { Pixel(0, 1), Pixel(1, 0), Pixel(-1, 0), Pixel(0, -1) };
		for (Pixel p : directions) {
			if (surface->contains(next + p) && surface->get_pixel(next + p) == original_colour) {
				surface->set_pixel(next + p, colour);
				stack.push_back(next + p);
			}
		}		
	}	
}

void Canvas::draw_line(Pixel P1, Pixel P2, int colour, int width) {
	double x = P2.x - P1.x;
	double y = P2.y - P1.y;
	double length = sqrt(x*x + y*y);


	if (length < 1)
	{
		SDL_Rect rect = { P1.x, P1.y, width, width };
		if (surface->contains(rect)) {
			surface->fill_rectangle(&rect, colour);
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
		if (surface->contains(rect)) {
			surface->fill_rectangle(&rect, colour);			
		}
		x += addx;
		y += addy;
	}

}
void Canvas::clear()
{	
	surface->fill_rectangle(&surface->rect, 0xFFFFFF);	
}

void Canvas::load_canvas(char* out_path)
{
	try {
		Surface *new_surface = new Surface(out_path);
		delete surface;
		for (Surface *backup_surface : saved_states) {
			delete backup_surface;
		}

		surface = new_surface;
		init_save_states();
	}
	catch (WrongExtension &e) {
		throw;
	}		
}

void Canvas::apply_filter(Filter &filter) {
	Surface *with_filter = surface->with_filter(filter);
	delete surface;
	surface = with_filter;
}

void Canvas::to_greyscale() {
	Surface *new_surf = surface->as_grayscale();
	delete(surface);
	surface = new_surf;
}

void Canvas::show_edges() {	
	int kernel_size = 3;
	float *kernel_vertical = new float[kernel_size*kernel_size]{ -0.25, 0, 0.25, -0.5, 0, 0.5, -0.25, 0, 0.25 };
	float *kernel_horizontal = new float[kernel_size*kernel_size]{ -0.25, -0.5, -0.25, 0, 0, 0, 0.25, 0.5, 0.25 };
	Filter vertical(kernel_size, kernel_vertical, false);
	Filter horizontal(kernel_size, kernel_horizontal, false);
	
	Surface *greyscale = surface->as_grayscale();
	Surface *vertical_lines = greyscale->with_filter(vertical);
	Surface *horizontal_lines = greyscale->with_filter(horizontal);
	Surface *blended = horizontal_lines->blend(vertical_lines, &horizontal_lines->rect);

	delete surface;
	delete greyscale;
	delete vertical_lines;
	delete horizontal_lines;
	
	surface = blended;
}

