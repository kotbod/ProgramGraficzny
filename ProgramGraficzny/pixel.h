#pragma once

class Pixel {
public:
	int x;
	int y;
	
	Pixel();
	Pixel(Pixel& p);
	Pixel(Pixel&& p);
	Pixel operator=(Pixel & p);
	Pixel operator-(Pixel & p);
	Pixel(int x, int y);

};