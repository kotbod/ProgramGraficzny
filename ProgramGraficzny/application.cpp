#include <SDL.h>

#include <iostream>
#include <vector>
#include "application.h"
#include "pencil.h"
#include "Canvas.h"
#include"pixel.h"
#include"Button.h"

#define MENU_HEIGHT 70

using namespace std;

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 400;

Pixel Application::mouse_position;

int Application::CHANGE_COLOUR;

void Application::set_up_events() {
	CHANGE_COLOUR = SDL_RegisterEvents(1);
}

Application::Application() : display(SCREEN_WIDTH, SCREEN_HEIGHT), quit(false) {
	set_up_events();
	palette = new vector<Button*>();
}
Application::~Application() {
	delete main_canvas;
	delete active_tool;
}

void Application::start() {
	main_canvas = new Canvas(400, 400);
	active_tool = new Pencil(main_canvas);
	Pixel start = Pixel(10, 10);
	Pixel size = Pixel(20, 20);
	palette->push_back(new Button(0xFF0000, start, start + size, CHANGE_COLOUR));
	palette->push_back(new Button(0x00FF00, Pixel(start.x + size.x * 1, start.y), Pixel(start.x + size.x * 1, start.y) + size, CHANGE_COLOUR));
	palette->push_back(new Button(0x0000FF, Pixel(start.x + size.x * 2, start.y), Pixel(start.x + size.x * 2, start.y) + size, CHANGE_COLOUR));
	palette->push_back(new Button(0x000000, Pixel(start.x + size.x * 3, start.y), Pixel(start.x + size.x * 3, start.y) + size, CHANGE_COLOUR));
	palette->push_back(new Button(0xFFFFFF, Pixel(start.x + size.x * 4, start.y), Pixel(start.x + size.x * 4, start.y) + size, CHANGE_COLOUR));
	palette->push_back(new Button(0x00FFFF, Pixel(start.x + size.x * 5, start.y), Pixel(start.x + size.x * 5, start.y) + size, CHANGE_COLOUR));
	palette->push_back(new Button(0xFFFF00, Pixel(start.x + size.x * 6, start.y), Pixel(start.x + size.x * 6, start.y) + size, CHANGE_COLOUR));
	palette->push_back(new Button(0xFF00FF, Pixel(start.x + size.x * 7, start.y), Pixel(start.x + size.x * 7, start.y) + size, CHANGE_COLOUR));
	loop();
}


void Application::draw_everything() {
	// wyswietl obszar plotna
	SDL_Rect dstrect = { 0, MENU_HEIGHT, main_canvas->surface->w,main_canvas->surface->h };
	SDL_BlitSurface(main_canvas->surface, NULL, display.window_surface, &dstrect);
	for (Button* c : *palette) {
		c->draw(&display);
	}

	display.update();
}

void Application::handle_events() {
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT) {
			quit = true;
		}
		else if (e.type == SDL_MOUSEMOTION) {
			mouse_position = Pixel(e.motion.x, e.motion.y);
			cout << mouse_position.x << ", " << mouse_position.y << endl;
		}
		else {
			active_tool->handle_event(e);
			for (Button* c : *palette) {
				c->handle_event(e);
			}
		}
	}
}

void Application::loop() {
	while (!quit && mainEvent->type!=SDL_QUIT ) {
		active_tool->update();
		handle_events();
		draw_everything();
	}
}

Pixel Application::get_mouse_position()
{
	return mouse_position;
}

Pixel Application::get_canvas_position() {
	return mouse_position - Pixel(0, MENU_HEIGHT);
}

