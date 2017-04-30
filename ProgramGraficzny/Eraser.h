#pragma once

#include"pencil.h"
class Eraser :public Pencil
{
public:
	Eraser(int colour, int width, Canvas * canvas);
	~Eraser();
	virtual void update();
};