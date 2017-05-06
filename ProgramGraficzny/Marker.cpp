#include "Marker.h"


Marker::Marker(int colour, int width, Canvas * canvas) :Pencil(colour, width,canvas) {}
Marker::~Marker() {}

void Marker::update() {
	if (left_click) {
		// rysujemy
		Pixel temp = Pixel(0, 1);
		Pixel pos = Application::get_canvas_mouse_position();
		canvas->draw_line(previous_pos - temp * 3, pos - temp * 3, colour, 1);
		canvas->draw_line(previous_pos - temp * 2, pos - temp * 2, colour, 1);
		canvas->draw_line(previous_pos - temp, pos - temp, colour,1);
		canvas->draw_line(previous_pos, pos, colour, 1);
		canvas->draw_line(previous_pos + temp, pos + temp, colour, 1);
		canvas->draw_line(previous_pos + temp * 2, pos + temp * 2, colour, 1);
		canvas->draw_line(previous_pos + temp * 3, pos + temp * 3, colour, 1);
		previous_pos = pos;
	}
}
