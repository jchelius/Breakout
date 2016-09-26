#ifndef PADDLE_H
#define PADDLE_H

#include "../include/Graphics.hpp"


class Paddle
{
private:
	Graphics* _graphics;
	int _x, _y;
	const int _MOVE_AMOUNT;
	const Color _COLOR;
	const int _WIDTH, _HEIGHT;
public:
	Paddle(Graphics* graphics);
	~Paddle();
	void update();
	void render();
	void moveLeft() { setX(_x - _MOVE_AMOUNT); }
	void moveRight() { setX(_x + _MOVE_AMOUNT); }
	void setX(const int x);
	void setY(const int y);
	const int getX() const { return _x; }
	const int getY() const { return _y; }
	const int getW() const { return _WIDTH; }
	const int getH() const { return _HEIGHT; }
	void reset();
};


#endif 