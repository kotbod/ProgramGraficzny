#include "Marker.h"


Marker::Marker(int width, Canvas * canvas) :Pencil( width,canvas) {}

void Marker::update() {
	if (left_click) {
		// rysujemy
		Pixel temp = Pixel(0, 1);
		Pixel pos = Application::get_canvas_position();
		if (pos.y > 0 && previous_pos.y > 0 && pos.x>0 && previous_pos.x>0 && pos.y<canvas->surface->h && previous_pos.y < canvas->surface->h && pos.x<canvas->surface->w && previous_pos.x < canvas->surface->w)
		{
			//rysujemy linie
			canvas->draw_line(previous_pos - temp * 3, pos - temp * 3, colour, 1);
			canvas->draw_line(previous_pos - temp * 2, pos - temp * 2, colour, 1);
			canvas->draw_line(previous_pos - temp, pos - temp, colour,1);
			canvas->draw_line(previous_pos, pos, colour, 1);
			canvas->draw_line(previous_pos + temp, pos + temp, colour, 1);
			canvas->draw_line(previous_pos + temp * 2, pos + temp * 2, colour, 1);
			canvas->draw_line(previous_pos + temp * 3, pos + temp * 3, colour, 1);
		}
		previous_pos = pos;
	}
}
