#pragma once

#include <SDL.h>
#include "tool.h"
#include "Canvas.h"
#include "application.h"
#include"Button.h"

class Pencil : public Tool {
protected:
	int colour=0;
	int width = 1;
	Canvas* canvas;
	bool left_click;
	Pixel previous_pos;
public:
	Pencil(int colour, int width, Canvas * canvas);

	virtual void handle_event(SDL_Event& e);
	virtual void update();
};