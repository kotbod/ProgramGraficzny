#pragma once

#include"pencil.h"
#include"Canvas.h"

class Marker :public Pencil {

public:
	Marker(int width,Canvas* canvas);
	~Marker();
	virtual void update();
};
