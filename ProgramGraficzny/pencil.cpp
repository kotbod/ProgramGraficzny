#include "pencil.h"
#include <iostream>

using namespace std;

Pencil::Pencil(Canvas* canvas): canvas(canvas), left_click(false) {}

void Pencil::handle_event(SDL_Event & e)
{
	if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
		left_click = true;
		previous_pos = Application::get_canvas_position();
	}
	else if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
		left_click = false;
	}
	else if (e.type == Application::CHANGE_COLOUR) {
		colour = (int)e.user.data1;
	}

}

void Pencil::update() {
	if (left_click) {
		// rysujemy
		Pixel pos = Application::get_canvas_position();
		if (pos.y > 0 && previous_pos.y > 0 && pos.x>0 &&previous_pos.x>0 && pos.y<canvas->surface->h && previous_pos.y < canvas->surface->h && pos.x<canvas->surface->w && previous_pos.x < canvas->surface->w)
		{
			//rysujemy linie
			canvas->draw_line(previous_pos, pos, colour, 1);									
		}
		previous_pos = pos;
	}
}
