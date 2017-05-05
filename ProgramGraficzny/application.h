#pragma once
#include <vector>

#include "Canvas.h"
#include "display.h"
#include "tool.h"
#include "GUIelement.h"

using namespace std;

class Application {
private:
	int current_colour;
	static Pixel mouse_position;
	static Pixel canvas_mouse_pos;
	Canvas *main_canvas;
	Display display;
	Tool *active_tool;
	vector<GUIelement*> *palette;
	bool quit;
public:
	Application(void);
	~Application();

	static int CHANGE_COLOUR;
	static int CHANGE_WIDTH;
	static int CHANGE_TO_PENCIL;
	static int CHANGE_TO_MARKER;
	static int CHANGE_TO_ERASER;
	static int CHANGE_TO_PAINT;
	static int NEW_FILE;
	static int SAVE;
	static int OPEN;
	static int GO_BACK;

	void start();
	void set_up_events();
	void handle_events();
	void loop();
	static Pixel get_mouse_position();
	static Pixel get_canvas_position();
	void draw_everything();
};
