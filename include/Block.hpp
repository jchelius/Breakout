#ifndef BLOCK_H
#define BLOCK_H

#include "Graphics.hpp"


class Block
{
	friend class Game;
private:
	int _x, _y;
	int _w, _h;
	Color _color;
	Graphics* _graphics;
public:
	static const int WIDTH, HEIGHT;
public:
	Block(Graphics* graphics, const int x, const int y, const int w, const int h);
	~Block();
	const int getX() const { return _x; }
	const int getY() const { return _y; }
	const int getW() const { return _w; }
	const int getH() const { return _h; }
	void render();
};


#endif //BLOCK_H
