#include <SDL.h>

#include <iostream>
#include <vector>
#include "application.h"
#include "pencil.h"
#include "Canvas.h"
#include"pixel.h"
#include"Button.h"
#include "Button_tool.h"
#include"Marker.h"
#include"Eraser.h"
#include"Button_width.h"
#include "paint.h"
#include "nfd.h"
#include "colour_display.h"

#define MENU_HEIGHT 70

using namespace std;

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 400;

Pixel Application::mouse_position;

int Application::CHANGE_COLOUR;
int Application::CHANGE_WIDTH;
int Application::CHANGE_TO_PENCIL;
int Application::CHANGE_TO_MARKER;
int Application::CHANGE_TO_ERASER;
int Application::CHANGE_TO_PAINT;
int Application::NEW_FILE;
int Application::SAVE;
int Application::OPEN;

void Application::set_up_events() {
	CHANGE_COLOUR = SDL_RegisterEvents(1);
	CHANGE_TO_PENCIL = SDL_RegisterEvents(1);
	CHANGE_TO_MARKER = SDL_RegisterEvents(1);
	CHANGE_TO_ERASER = SDL_RegisterEvents(1);
	NEW_FILE = SDL_RegisterEvents(1);
	CHANGE_WIDTH = SDL_RegisterEvents(1);
	CHANGE_TO_PAINT = SDL_RegisterEvents(1);
	SAVE = SDL_RegisterEvents(1);
	OPEN = SDL_RegisterEvents(1);
}

Application::Application() : display(SCREEN_WIDTH, SCREEN_HEIGHT), quit(false) {
	set_up_events();
	palette = new vector<GUIelement*>();
}
Application::~Application() {
	delete main_canvas;
	delete active_tool;
}

void Application::start() {
	
	main_canvas = new Canvas(400, 400);
	active_tool = new Pencil(1,main_canvas);
	Pixel start = Pixel(10, 10);
	Pixel size = Pixel(30, 30);
	palette->push_back(new Button(0xFF0000, start, start + size, CHANGE_COLOUR));
	palette->push_back(new Button(0x00FF00, Pixel(start.x + size.x * 1, start.y), Pixel(start.x + size.x * 1, start.y) + size, CHANGE_COLOUR));
	palette->push_back(new Button(0x0000FF, Pixel(start.x + size.x * 2, start.y), Pixel(start.x + size.x * 2, start.y) + size, CHANGE_COLOUR));
	palette->push_back(new Button(0x000000, Pixel(start.x + size.x * 3, start.y), Pixel(start.x + size.x * 3, start.y) + size, CHANGE_COLOUR));
	palette->push_back(new Button(0xFFFFFF, Pixel(start.x + size.x * 4, start.y), Pixel(start.x + size.x * 4, start.y) + size, CHANGE_COLOUR));
	palette->push_back(new Button(0x00FFFF, Pixel(start.x + size.x * 5, start.y), Pixel(start.x + size.x * 5, start.y) + size, CHANGE_COLOUR));
	palette->push_back(new Button(0xFFFF00, Pixel(start.x + size.x * 6, start.y), Pixel(start.x + size.x * 6, start.y) + size, CHANGE_COLOUR));
	palette->push_back(new Button(0xFF00FF, Pixel(start.x + size.x * 7, start.y), Pixel(start.x + size.x * 7, start.y) + size, CHANGE_COLOUR));

	start = Pixel(10, 40);
	palette->push_back(new Button_tool(display.load_texture("pic/pencil.png"), start, start + size, CHANGE_TO_PENCIL));
	palette->push_back(new Button_tool(display.load_texture("pic/marker.png"), Pixel(start.x + size.x * 1, start.y), Pixel(start.x + size.x * 1, start.y) + size, CHANGE_TO_MARKER));
	palette->push_back(new Button_tool(display.load_texture("pic/eraser1.png"), Pixel(start.x + size.x * 2, start.y), Pixel(start.x + size.x * 2, start.y) + size, CHANGE_TO_ERASER));
	palette->push_back(new Button_tool(display.load_texture("pic/paint.png"), Pixel(start.x + size.x * 3, start.y), Pixel(start.x + size.x * 3, start.y) + size, CHANGE_TO_PAINT));
	palette->push_back(new Button_tool(display.load_texture("pic/new_file.png"), Pixel(start.x + size.x * 4, start.y), Pixel(start.x + size.x * 4, start.y) + size, NEW_FILE));
	palette->push_back(new Button_tool(display.load_texture("pic/DISK.png"), Pixel(start.x + size.x * 5, start.y), Pixel(start.x + size.x * 5, start.y) + size, SAVE));
	palette->push_back(new Button_tool(display.load_texture("pic/OPEN.png"), Pixel(start.x + size.x * 6, start.y), Pixel(start.x + size.x * 6, start.y) + size, OPEN));
	start = Pixel(270, 5);
	size = Pixel(38, 15);

	palette->push_back(new Button_width(1,display.load_texture("pic/line1.bmp"), start, start + size, CHANGE_WIDTH));
	palette->push_back(new Button_width(3,display.load_texture("pic/line2.bmp"), Pixel(start.x, start.y + size.y * 1), Pixel(start.x, start.y + size.y * 1) + size, CHANGE_WIDTH));
	palette->push_back(new Button_width(5,display.load_texture("pic/line3.bmp"), Pixel(start.x, start.y + size.y * 2), Pixel(start.x, start.y + size.y * 2) + size, CHANGE_WIDTH));
	palette->push_back(new Button_width(7,display.load_texture("pic/line4.bmp"), Pixel(start.x, start.y + size.y * 3), Pixel(start.x, start.y + size.y * 3) + size, CHANGE_WIDTH));

	start = Pixel(320, 10);
	size = Pixel(40, 40);
	palette->push_back(new ColourDisplay(0, start, size));

	loop();
}


void Application::draw_everything() {
	// wyswietl obszar plotna
	SDL_Rect dstrect = { 0, MENU_HEIGHT, main_canvas->surface->w,main_canvas->surface->h };
	SDL_BlitSurface(main_canvas->surface, NULL, display.window_surface, &dstrect);
	for (GUIelement* c : *palette) {
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
		}
		else if (e.type == CHANGE_TO_PENCIL)
		{
			
			delete active_tool;
			active_tool = new Pencil(1,main_canvas);

		}
		else if (e.type == CHANGE_TO_MARKER)
		{
			delete active_tool;
			active_tool = new Marker(1,main_canvas);

		}
		else if (e.type == CHANGE_TO_ERASER)
		{
			delete active_tool;
			active_tool = new Eraser(5,main_canvas);

		}
		else if (e.type == NEW_FILE)
		{
			main_canvas->clear();

		}
		else if (e.type == CHANGE_TO_PAINT) {
			delete active_tool;
			active_tool = new Paint(main_canvas);
		}
		else if (e.type == OPEN) {
			nfdchar_t *outPath = NULL;
			nfdresult_t result = NFD_OpenDialog(NULL, NULL, &outPath);
			if (outPath!=NULL) {
				cout << outPath << endl;
				main_canvas->load_canvas(outPath);

				free(outPath);
			}
		}
		else if (e.type == SAVE) {
			nfdchar_t *outPath = NULL;
			//nfdresult_t result = NFD_OpenDialog(NULL, NULL, &outPath);
			nfdresult_t w = NFD_SaveDialog(NULL, NULL, &outPath);
			
			if (w) {
				int a = SDL_SaveBMP(main_canvas->surface, outPath);

				free(outPath);
			}

		}
		 if (e.type == CHANGE_COLOUR) {
			current_colour = (int)e.user.data1;
		}
		
		active_tool->handle_event(e);
		for (GUIelement* c : *palette) {
			c->handle_event(e);
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

