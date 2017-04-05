#pragma once

#include"pencil.h"
#include"Canvas.h"

class Marker :public Pencil {

public:
	Marker(Canvas* canvas);
	~Marker();
	virtual void update();
};
