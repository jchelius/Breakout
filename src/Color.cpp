#include "../include/Color.hpp"
#include "../include/Random.hpp"


const Color Color::RED = { 255, 0, 0 };
const Color Color::GREEN = { 0, 255, 0 };
const Color Color::BLUE = { 0, 0, 255 };
const Color Color::ORANGE = { 255, 128, 0 };
const Color Color::YELLOW = { 255, 255, 0 };
const Color Color::BROWN = { 51, 25 , 0 };
const Color Color::WHITE = { 255, 255, 255 };
const Color Color::BLACK = { 0, 0, 0 };

Color::Color(const int r, const int g, const int b, const int a):
	r(r),
	g(g),
	b(b),
	a(a)
{
	
}

Color::Color():
	r(255),
	g(255),
	b(255),
	a(255)
{

}

std::ostream& operator<<(std::ostream& os, const Color& color)
{
	os << "(" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << ")";
	return os;
}

const bool Color::operator!=(const Color& other) const
{
	return !operator==(other);
}

const bool Color::operator==(const Color& other) const
{
	return other.r == r && other.g == g && other.b == b && other.a == a;
}

const Color Color::randColor()
{
	Color color;
	color.r = Random::randint(0, 255);
	color.g = Random::randint(0, 255);
	color.b = Random::randint(0, 255);
	return color;
}

const Color Color::randColor(const Color& exc)
{
	Color color = exc;
	while(color == exc)
	{
		color.r = Random::randint(0, 255);
		color.g = Random::randint(0, 255);
		color.b = Random::randint(0, 255);
	}
	return color;
}