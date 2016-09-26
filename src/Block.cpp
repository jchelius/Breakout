#include "../include/Block.hpp"
#include "../include/Random.hpp"


Block::Block(Graphics* graphics, const int x, const int y, const int w, const int h):
	_x(x),
	_y(y),
	_w(w),
	_h(h),
	_graphics(graphics)
{
	_color = Color::randColor(Color::BLACK);
}

Block::~Block()
{

}

void Block::render()
{
	const SDL_Rect rect = { _x, _y, _w, _h };
	_graphics->setDrawColor(_color);
	_graphics->drawFilledRect(rect);
}