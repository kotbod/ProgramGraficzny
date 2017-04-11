#include "Button_width.h"

Button_width::Button_width(int width, SDL_Surface*surface,Pixel top_left, Pixel bottom_right, int event_type):width(width),surface(surface), top_left(top_left), bottom_right(bottom_right), event_type(event_type)
{
}

Button_width::~Button_width()
{
}

void Button_width::update()
{
}

void Button_width::handle_event(SDL_Event & e)
{
	if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT && e.motion.x > top_left.x &&e.motion.x<bottom_right.x &&e.motion.y>top_left.y && e.motion.y < bottom_right.y)
	{
		SDL_Event event;
		SDL_memset(&event, 0, sizeof(event)); /* or SDL_zero(event) */
		event.type = event_type;
		event.user.data1 = (void*)width;
		SDL_PushEvent(&event);
	}
}

void Button_width::draw(Display * display)
{
	SDL_Rect rect = { top_left.x,top_left.y,bottom_right.x - top_left.x,bottom_right.y - top_left.y };
	SDL_BlitScaled(surface, NULL, display->window_surface, &rect);
}
