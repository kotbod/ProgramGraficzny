#pragma once

class Pixel {
public:
	int x;
	int y;
	
	Pixel();
	Pixel(const Pixel& p);
	Pixel(Pixel&& p);
	Pixel operator=(Pixel & p);
	Pixel operator-(Pixel & p);
	Pixel operator+(Pixel & p);
	Pixel operator*(int i);
	Pixel(int x, int y);

};