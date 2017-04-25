#pragma once

#include "GUIelement.h"
#include "pixel.h"

class ColourDisplay : public GUIelement {
private:
	int colour;
	Pixel pos;
	Pixel size;
public:
	ColourDisplay(int colour, Pixel pos, Pixel size);
	virtual void update();
	virtual void handle_event(SDL_Event &e);
	virtual void draw(Display* display);
};