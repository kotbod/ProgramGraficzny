#include "paint.h"

Paint::Paint(Canvas * canvas): canvas(canvas) {}

void Paint::handle_event(SDL_Event & e)
{
	if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
		canvas->backup_surface();
		canvas->fill_at(Application::get_canvas_position(), colour);
	}
	else if (e.type == Application::CHANGE_COLOUR) {
		colour = (int)e.user.data1;
	}
}

void Paint::update() {}
