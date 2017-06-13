#pragma once
#include <vector>

#include "Canvas.h"
#include "display.h"
#include "tool.h"
#include "GUIelement.h"
#include "warning.h"
#include "GUI_label.h"

using namespace std;

class NoOpenPath : public exception {
public:
	virtual const char* what() noexcept {
		return "Nie podano sciezki pliku!\n";
	}
};

class NoSavePath : public exception {
public:
	virtual const char* what() noexcept {
		return "Nie podano sciezki pliku!\n";
	}
};

class Application {
private:
	int current_colour;
	static Pixel mouse_position;
	static Pixel canvas_mouse_pos;
	Canvas *main_canvas;
	Display display;
	Tool *active_tool;
	vector<GUIelement*> *palette;
	GUI_label<Pixel> *coords_label;
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
	static int APPLY_LINEAR_BLUR;
	static int APPLY_GAUSSIAN_BLUR;
	static int TO_GREYSCALE;
	static int SHOW_EDGES;

	void start();
	void set_up_events();
	void handle_events();
	void loop();
	void load();
	void save();
	static Pixel get_mouse_position();
	static Pixel get_canvas_mouse_position();
	void draw_everything();
};
