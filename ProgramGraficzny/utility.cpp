#pragma once

#include "utility.h"

// Check if the pixel p is inside the rectangle r
bool is_inside(Pixel &p, SDL_Rect &r) {
	return p.x >= r.x && p.x < r.x + r.w && p.y >= r.y && p.y < r.y + r.h;
}