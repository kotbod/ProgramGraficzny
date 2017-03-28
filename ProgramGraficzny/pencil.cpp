#include "pencil.h"
#include <iostream>

using namespace std;

Pencil::Pencil(Canvas* canvas): canvas(canvas), left_click(false) {}

void Pencil::handle_event(SDL_Event & e)
{
	if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
		left_click = true;
		SDL_GetMouseState(&previous_pos.x, &previous_pos.y);
	}
	if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
		left_click = false;
	}

}

void Pencil::update() {
	if (left_click) {
		// rysujemy
		Pixel pos;
		SDL_GetMouseState(&pos.x, &pos.y);
		//rysujemy linie
		canvas->draw_line(previous_pos, pos,0);
		previous_pos = pos;
	}
}
