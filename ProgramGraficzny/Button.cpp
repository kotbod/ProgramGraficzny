#include "Button.h"
#include<iostream>
#include "application.h"
using namespace std;


Button::Button(int colour, Pixel top_left, Pixel bottom_right, int event_type):colour(colour),top_left(top_left),bottom_right(bottom_right), event_type(event_type)
{
}

Button::~Button()
{
}

void Button::update()
{
}

void Button::handle_event(SDL_Event &e)
{

	if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT && e.motion.x > top_left.x &&e.motion.x<bottom_right.x &&e.motion.y>top_left.y && e.motion.y < bottom_right.y)
	{
		SDL_Event event;
		SDL_memset(&event, 0, sizeof(event)); /* or SDL_zero(event) */
		event.type = event_type;
		event.user.data1 = (void*)colour;
		SDL_PushEvent(&event);
	}

		

}

void Button::draw(Display* display)

{
	const SDL_Rect rect = {top_left.x,top_left.y,bottom_right.x-top_left.x,bottom_right.y-top_left.y };
	SDL_FillRect(display->window_surface, &rect, colour);
}
