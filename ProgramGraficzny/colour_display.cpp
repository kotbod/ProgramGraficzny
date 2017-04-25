#include "colour_display.h"
#include "application.h"
#include<iostream>
using namespace std;
#pragma once

ColourDisplay::ColourDisplay(int colour, Pixel pos, Pixel size): colour(colour), pos(pos), size(size)
{
}

void ColourDisplay::update()
{
}

void ColourDisplay::handle_event(SDL_Event & e)
{
	if (e.type == Application::CHANGE_COLOUR) {
		colour = (int)e.user.data1;
		cout << colour << endl;
	}
}

void ColourDisplay::draw(Display * display)
{
	SDL_Rect rect = { pos.x, pos.y, size.x, size.y };
	SDL_FillRect(display->window_surface, &rect, colour);
}
