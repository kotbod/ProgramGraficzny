#pragma once

#include"pencil.h"
class Eraser :public Pencil
{
public:

	Eraser(Canvas *canvas);
	~Eraser();
	virtual void update();
};