#include "Eraser.h"
#include"Canvas.h"

Eraser::Eraser(int colour, int width,Canvas * canvas): Pencil(colour, width,canvas)
{
}

Eraser::~Eraser()
{
}


void Eraser::update()
{
	if (left_click) {				
		Pixel pos = Application::get_canvas_mouse_position();
		if (canvas->surface->contains(pos) && canvas->surface->contains(previous_pos))
		{			
			canvas->draw_line(previous_pos, pos, 0xFFFFFF, width);
		}
		previous_pos = pos;
	}
}
