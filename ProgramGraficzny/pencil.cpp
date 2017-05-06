#include "pencil.h"
#include <iostream>

using namespace std;

Pencil::Pencil(int colour, int width,Canvas* canvas):colour(colour), width(width), canvas(canvas), left_click(false) {}

void Pencil::handle_event(SDL_Event & e)
{
	if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
		left_click = true;
		canvas->backup_surface();
		previous_pos = Application::get_canvas_mouse_position();
	}
	else if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
		left_click = false;
	}
	else if (e.type == Application::CHANGE_COLOUR) {
		colour = *(int*)e.user.data1;
	}
	else if (e.type == Application::CHANGE_WIDTH) {
		width = *(int*)e.user.data1;
	}

}

void Pencil::update() {
	if (left_click) {
		// rysujemy
		Pixel pos = Application::get_canvas_mouse_position();		
		//rysujemy linie
		canvas->draw_line(previous_pos, pos, colour, width);											
		previous_pos = pos;
	}
}
