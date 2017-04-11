#pragma once
#include"GUIelement.h"
#include"pixel.h"

class Button_width :public GUIelement
{
	SDL_Surface* surface;
	int width;
	Pixel top_left;
	Pixel bottom_right;
	int event_type;
public:
	Button_width(int width,SDL_Surface*surface, Pixel top_left, Pixel bottom_right, int event_type);
	~Button_width();

	virtual void update();
	virtual void handle_event(SDL_Event &e);
	virtual void draw(Display* display);
};
