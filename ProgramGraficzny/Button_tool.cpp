
#include"Button_tool.h"
Button_tool::Button_tool(SDL_Surface* Picture, Pixel top_left, Pixel bottom_right, int event_type) :Picture(Picture), top_left(top_left), bottom_right(bottom_right), event_type(event_type)
{
}

Button_tool::~Button_tool()
{
}

void Button_tool::update()
{
}

void Button_tool::handle_event(SDL_Event &e)
{

	if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT && e.motion.x > top_left.x &&e.motion.x<bottom_right.x &&e.motion.y>top_left.y && e.motion.y < bottom_right.y)
	{
		SDL_Event event;
		SDL_memset(&event, 0, sizeof(event)); /* or SDL_zero(event) */
		event.type = event_type;
		SDL_PushEvent(&event);
	}



}

void Button_tool::draw(Display* display)

{
	SDL_Rect rect = { top_left.x,top_left.y,bottom_right.x - top_left.x,bottom_right.y - top_left.y };
	SDL_BlitScaled(Picture, NULL, display->window_surface, &rect);
}