#include "Button_tool.h"
#include "utility.h"

Button_tool::Button_tool(SDL_Surface* Picture, Pixel top_left, Pixel size, int event_type) :Picture(Picture), event_type(event_type)
{
	rect = { top_left.x, top_left.y, size.x, size.y };
}

Button_tool::~Button_tool()
{
	// Picture should be loaded in in the Display class and dealocated there
}

void Button_tool::update()
{
}

void Button_tool::handle_event(SDL_Event &e)
{
	Pixel mouse_pos(e.motion.x, e.motion.y);
	if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT && is_inside(mouse_pos, rect))
	{
		e.type = 0; // 'Delete' the event, so nothing else picks up on it. Kind of weird. Should change it.
		SDL_Event event; 
		SDL_memset(&event, 0, sizeof(event)); /* or SDL_zero(event) */
		event.type = event_type;
		SDL_PushEvent(&event);
	}
}

void Button_tool::draw(Display* display)
{
	SDL_BlitScaled(Picture, NULL, display->window_surface, &rect);
}