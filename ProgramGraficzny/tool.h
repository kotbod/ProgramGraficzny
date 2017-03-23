#pragma once
#include "SDL.h"
class Tool {
public:
	virtual void handle_event(SDL_Event& e) = 0;
};