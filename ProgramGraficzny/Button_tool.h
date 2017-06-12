#pragma once

#include"GUIelement.h"

#include"display.h"
#include"pixel.h"

class Button_tool :public GUIelement  {
private:
	SDL_Surface* Picture;
	SDL_Rect rect;
	int event_type;
public:
	Button_tool(SDL_Surface* Picture, Pixel top_left, Pixel size, int event_type);
	~Button_tool();

	virtual void update();
	virtual void handle_event(SDL_Event &e);
	virtual void draw(Display* display);
};
