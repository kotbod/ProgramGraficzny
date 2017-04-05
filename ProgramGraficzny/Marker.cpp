#include "Marker.h"


Marker::Marker(Canvas * canvas) :Pencil( canvas) {}

void Marker::update() {
	if (left_click) {
		// rysujemy
		Pixel temp = Pixel(1, 1);
		Pixel pos = Application::get_canvas_position();
		if (pos.y > 0 && previous_pos.y > 0 && pos.x>0 && previous_pos.x>0 && pos.y<canvas->surface->h && previous_pos.y < canvas->surface->h && pos.x<canvas->surface->w && previous_pos.x < canvas->surface->w)
		{
			//rysujemy linie
			canvas->draw_line(previous_pos, pos, colour);
			canvas->draw_line(previous_pos+temp, pos+temp, colour);
			canvas->draw_line(previous_pos-temp, pos-temp, colour);
		}
		previous_pos = pos;
	}
}
