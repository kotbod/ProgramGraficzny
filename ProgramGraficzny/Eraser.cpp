#include "Eraser.h"
#include"Canvas.h"

Eraser::Eraser(int width,Canvas * canvas): Pencil(width,canvas)
{
}

Eraser::~Eraser()
{
}


void Eraser::update()
{
	if (left_click) {
		// rysujemy
		Pixel temp = Pixel(1, 1);
		Pixel pos = Application::get_canvas_position();
		if (pos.y > 0 && previous_pos.y > 0 && pos.x>0 && previous_pos.x>0 && pos.y<canvas->surface->h && previous_pos.y < canvas->surface->h && pos.x<canvas->surface->w && previous_pos.x < canvas->surface->w)
		{
			//rysujemy linie
			canvas->draw_line(previous_pos, pos, 0xFFFFFF, width);
		}
		previous_pos = pos;
	}
}
