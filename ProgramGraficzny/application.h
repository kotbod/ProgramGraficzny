#pragma once
#include "Canvas.h"
#include "display.h"
#include "tool.h"
#include "pencil.h"

class Application {
private:
	Canvas *main_canvas;
	Display display;
	Tool *active_tool;
	SDL_Event* mainEvent = new SDL_Event();
	bool quit;
public:
	Application(void);
	~Application();

	void start();
	void set_up_events();
	void handle_events();
	void loop();
	void draw_everything();
};
