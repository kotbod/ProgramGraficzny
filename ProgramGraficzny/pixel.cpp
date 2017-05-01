#include "pixel.h"

Pixel::Pixel(): Pixel(0, 0) {}
Pixel::Pixel(int x, int y): x(x), y(y) {}
Pixel::Pixel(const Pixel& p) {
	x = p.x;
	y = p.y;
}
Pixel::Pixel(Pixel&& p) {
	x = p.x;
	y = p.y;
}

Pixel Pixel::operator=(Pixel& p) {
	x = p.x;
	y = p.y;
	return *this;
}

Pixel Pixel::operator-(Pixel& p) {
	return Pixel(x - p.x, y - p.y);
}

Pixel Pixel::operator+(Pixel& p) {
	return Pixel(x + p.x, y + p.y);
}

Pixel Pixel::operator*(int i)
{
	return Pixel(x * i, y * i);
}

bool Pixel::operator==(Pixel &p)
{
	return x == p.x && y == p.y;
}

bool Pixel::operator!=(Pixel &p)
{
	return !(x == p.x && y == p.y);
}

std::ostream& operator<<(std::ostream& os, const Pixel& obj)
{
	os << "(" << obj.x << ", " << obj.y << ")";
	return os;
}