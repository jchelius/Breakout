#ifndef BALL_H
#define BALL_H

#include "../include/Graphics.hpp"
#include "../include/Paddle.hpp"
#include "../include/Block.hpp"


class Ball
{
private:
	Graphics* _graphics;
	int _x, _y;
	int _vx, _vy;
	const int _VEL_MAG;
	const Color _COLOR;
public:
	const int WIDTH, HEIGHT;
public:
	Ball(Graphics* graphics);
	~Ball();
	void bounceOffPaddle(const Paddle& paddle);
	void update();
	void render();
	void reset();
	void setX(const int x);
	void setY(const int y);
	const int getX() const { return _x; }
	const int getY() const { return _y; }
	const bool collidesWithPaddle(const Paddle& paddle) const;
	const bool collidesWithBlock(const Block& block) const;
	const bool fellOffScreen() const;
	const bool hasStarted() const;
	void start();
};


#endif //BALL_H