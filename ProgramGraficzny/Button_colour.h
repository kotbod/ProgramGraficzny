#pragma once

#include "GUIelement.h"
#include"display.h"
#include"pixel.h"

class Button_colour : public GUIelement {


	int colour;
	Pixel top_left;
	Pixel bottom_right;
	int event_type;
public:


	Button_colour(int colour,Pixel top_left, Pixel bottom_right, int event_type);
	~Button_colour();

	virtual void update();
	virtual void handle_event(SDL_Event &e);
	virtual void draw(Display* display);

};
