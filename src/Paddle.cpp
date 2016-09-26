#include "../include/Paddle.hpp"


Paddle::Paddle(Graphics* graphics):
	_graphics(graphics),
	_COLOR(Color::WHITE),
	_MOVE_AMOUNT(10),
	_WIDTH(100),
	_HEIGHT(_WIDTH / 5)
{
	reset();
}

Paddle::~Paddle()
{

}

void Paddle::update()
{
	
}

void Paddle::setX(const int x)
{
	if (x < 0 || x > _graphics->getWidth() - _WIDTH)
	{
		return;
	}
	_x = x;
}

void Paddle::setY(const int y)
{
	if (_y < -_HEIGHT || _y > _graphics->getHeight() - _HEIGHT)
	{
		return;
	}
	_y = y;
}

void Paddle::render()
{
	_graphics->setDrawColor(_COLOR);
	const SDL_Rect rect = { _x, _y, _WIDTH, _HEIGHT };
	_graphics->drawFilledRect(rect);
}

void Paddle::reset()
{
	_x = _graphics->getWidth() / 2 - _WIDTH / 2;
	_y = _graphics->getHeight() - _HEIGHT;
}