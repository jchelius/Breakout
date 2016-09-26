#ifndef COLOR_H
#define COLOR_H

#include <SDL2/SDL.h>
#include <iostream>


class Color
{
public:
	int r, g, b, a;
	static const Color RED, GREEN, BLUE, ORANGE, YELLOW, BROWN, WHITE, BLACK;
public:
	Color(const int r, const int g, const int b, const int a = 255);
	Color();
	~Color(){ }
	friend std::ostream& operator<<(std::ostream& os, const Color& color);
	const bool operator!=(const Color& other) const;
	const bool operator==(const Color& other) const;
	static const Color randColor();
	static const Color randColor(const Color& exc);
};


#endif //COLOR_H