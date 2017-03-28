#include <SDL.h>

#include "application.h"
#include "pencil.h"
#include "Canvas.h"

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 400;

void Application::set_up_events() {

}

Application::Application() : display(SCREEN_WIDTH, SCREEN_HEIGHT), quit(false) {
	set_up_events();
}
Application::~Application() {
	delete main_canvas;
	delete active_tool;
}

void Application::start() {
	main_canvas = new Canvas(400, 400);
	active_tool = new Pencil(main_canvas);
	loop();
}


void Application::draw_everything() {
	// wyswietl obszar plotna
	SDL_Rect dstrect = { 0, 0, main_canvas->surface->w,main_canvas->surface->h };
	SDL_BlitSurface(main_canvas->surface, NULL, display.window_surface, &dstrect);

	display.update();
}

void Application::handle_events() {
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT) {
			quit = true;
		}
		else {
			active_tool->handle_event(e);
		}
	}
}

void Application::loop() {
	while (!quit && mainEvent->type!=SDL_QUIT ) {
		active_tool->update();
		handle_events();
		display.update();
		draw_everything();
	}
}
