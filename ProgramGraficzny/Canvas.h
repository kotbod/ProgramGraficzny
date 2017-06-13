#pragma once
#include <SDL.h>
#include "pixel.h"
#include "surface.h"
#include <exception>
#include <vector>
using namespace std;

const Uint32 WHITE = 0xFFFFFF;
const int MEMORY_FOR_SAVED_STATES = 300000000;

class Canvas {

private:
	vector<Surface *> saved_states;
	size_t amount_saved = 0;
public:
	Surface *surface;

	Canvas(int width_of_canvas, int height_of_canvas) ;
	~Canvas();
	void load_canvas(char* outPath);

	void init_save_states();	
	void backup_surface();
	void go_back();	
	
	void Canvas::fill_at(Pixel pos, int colour);
	void Canvas::draw_line(Pixel P1, Pixel P2, int colour, int width);
	void Canvas::clear();
	void Canvas::apply_filter(Filter &filter);
	void Canvas::show_edges();
	void Canvas::to_greyscale();

};


