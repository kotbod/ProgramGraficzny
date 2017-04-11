#pragma once
#include <vector>

#include "Canvas.h"
#include "display.h"
#include "tool.h"
#include "pencil.h"
#include"Button.h"

using namespace std;

class Application {
private:
	static Pixel mouse_position;
	Canvas *main_canvas;
	Display display;
	Tool *active_tool;
	vector<GUIelement*> *palette;
	SDL_Event* mainEvent = new SDL_Event();
	bool quit;
public:
	Application(void);
	~Application();

	static int CHANGE_COLOUR;
	static int CHANGE_WIDTH;
	static int CHANGE_TO_PENCIL;
	static int CHANGE_TO_MARKER;
	static int CHANGE_TO_ERASER;
	static int NEW_FILE;

	void start();
	void set_up_events();
	void handle_events();
	void loop();
	static Pixel get_mouse_position();
	static Pixel get_canvas_position();
	void draw_everything();
};
