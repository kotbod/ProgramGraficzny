#pragma once

#include <SDL.h>
#include "tool.h"
#include "Canvas.h"
#include "application.h"

class Paint : public Tool {
protected:
	int colour = 0;
	Canvas* canvas;
public:
	Paint(int colour, Canvas * canvas);
	virtual void handle_event(SDL_Event& e);
	virtual void update();
};