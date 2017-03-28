#pragma once

#include <SDL.h>
#include "tool.h"
#include "Canvas.h"

class Pencil : public Tool {
private:
	Canvas* canvas;
	bool left_click;
	Pixel previous_pos;
public:
	Pencil(Canvas* canvas);

	virtual void handle_event(SDL_Event& e);
	virtual void update();
};