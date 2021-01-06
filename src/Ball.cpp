#include "../include/Ball.hpp"
#include "../include/Paddle.hpp"
#include <iostream>
#include <cmath>


Ball::Ball(Graphics* graphics) :
	_graphics(graphics),
	_VEL_MAG(10),
	_COLOR(Color::WHITE),
	WIDTH(20),
	HEIGHT(20)
{
	reset();
}

Ball::~Ball()
{
	
}

void Ball::render()
{
	_graphics->setDrawColor(_COLOR);
	const SDL_Rect rect = { _x, _y, WIDTH, HEIGHT };
	_graphics->drawFilledRect(rect);
}

void Ball::update()
{
	_x += _vx;
	_y += _vy;
	if (_x <= 0 || _x >= _graphics->getWidth() - WIDTH)
	{
		_vx *= -1;
	}
	if(_y <= 0)
	{
		_vy *= -1;
	}
}

void Ball::reset()
{
	_x = _graphics->getWidth() / 2 - WIDTH / 2;
	_y = 3 * _graphics->getHeight() / 4;
	_vx = 0;
	_vy = 0;
}

void Ball::bounceOffPaddle(const Paddle& paddle)
{
	const double diffX = ((double)_x + WIDTH / 2) - ((double)paddle.getX() + paddle.getW() / 2);
	const double diffY = ((double)_y + HEIGHT / 2) - ((double)paddle.getY() + paddle.getH() / 2);
	_vx = (int) (_VEL_MAG *  diffX / paddle.getW());
	_vy = (int) (_VEL_MAG *  diffY / paddle.getH());
}

void Ball::setX(const int x)
{
	if (x < -WIDTH || x > _graphics->getWidth() - WIDTH)
	{
		return;
	}
	_x = x;
}

void Ball::setY(const int y)
{
	if (_y < -HEIGHT || _y > _graphics->getHeight() - HEIGHT)
	{
		return;
	}
	_y = y;
}

const bool Ball::collidesWithPaddle(const Paddle& paddle) const
{
	return _y + HEIGHT >= paddle.getY() && _x > paddle.getX() - WIDTH && _x < paddle.getX() + paddle.getW() + WIDTH;
}

const bool Ball::collidesWithBlock(const Block& block) const
{
	const int xDiff = std::abs((block.getX() + block.getW() / 2) - (_x + WIDTH / 2));
	const int yDiff = std::abs((block.getY() + block.getH() / 2) - (_y + HEIGHT / 2));
	return xDiff <= (block.getW() + WIDTH) / 2 && yDiff <= (block.getH() + HEIGHT) / 2;
}

const bool Ball::fellOffScreen() const
{
	return _y >= _graphics->getHeight() - HEIGHT;
}

const bool Ball::hasStarted() const
{
	return _vy != 0 || _vx != 0;
}

void Ball::start()
{
	_vx = 0;
	_vy = _VEL_MAG;
}