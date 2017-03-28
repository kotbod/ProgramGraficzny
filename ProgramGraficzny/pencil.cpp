#include "pencil.h"
#include <iostream>

using namespace std;

Pencil::Pencil(Canvas* canvas): canvas(canvas), left_click(false) {}

void Pencil::handle_event(SDL_Event & e)
{
	if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
		left_click = true;
	}
	if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
		left_click = false;
	}

}

void Pencil::update() {
	if (left_click) {
		// rysujemy
		SDL_GetMouseState(&x, &y);

		canvas->set_pixel(x, y, 0);
	}
}
