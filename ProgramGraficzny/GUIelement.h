#pragma once
#include"display.h"


class GUIelement {
public:
	virtual void update()=0;
	virtual void handle_event(SDL_Event &e)=0;
	virtual void draw(Display* display)=0;

};