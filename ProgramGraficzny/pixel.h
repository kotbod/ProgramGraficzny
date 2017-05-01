#pragma once

#include <string>
#include <sstream>
#include <ostream>

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
	bool operator==(Pixel &p);
	bool operator!=(Pixel &p);
	Pixel(int x, int y);

};

std::ostream& operator<<(std::ostream& os, const Pixel& obj);


