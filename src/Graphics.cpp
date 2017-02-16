#include "../include/Graphics.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>


Graphics::Graphics(const int width, const int height, const std::string& title):
	_width(width),
	_height(height)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();
	_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	resetTransformation();
	setDrawColor(Color::BLACK);
}

Graphics::~Graphics()
{
	for(auto const& itr : _textures)
	{
		SDL_DestroyTexture(itr.second);
	}
	_textures.clear();
	for(auto const& itr : _fonts)
	{
		TTF_CloseFont(itr.second);
	}
	_fonts.clear();
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Graphics::setDrawColor(const Color& color)
{
	_drawColor.r = (Uint8)color.r;
	_drawColor.g = (Uint8)color.g;
	_drawColor.b = (Uint8)color.b;
	_drawColor.a = (Uint8)color.a;
	SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
}

void Graphics::clear()
{
	SDL_RenderClear(_renderer);
}

SDL_Texture* Graphics::loadTexture(const std::string& file)
{
	if(_textures.find(file) == _textures.end())
	{
		SDL_Texture* texture = IMG_LoadTexture(_renderer, file.c_str());
		if(!texture)
		{
			std::cout << file << " failed to load" << std::endl;
		}
		_textures[file] = texture;
		return texture;
	}
	return _textures[file];
}

TTF_Font* Graphics::loadFont(const std::string& file, const int size)
{
	std::pair<std::string, int> pair;
	pair.first = file;
	pair.second = size;
	if (_fonts.find(pair) == _fonts.end())
	{
		TTF_Font* font = TTF_OpenFont(file.c_str(), size);
		if (!font)
		{
			std::cout << file << " failed to load" << std::endl;
		}
		_fonts[pair] = font;
		return font;
	}
	return _fonts[pair];
}

void Graphics::drawTexture(SDL_Texture* texture, const SDL_Rect& src, const int x, const int y, const double angle)
{
	if(!texture)
	{
		return;
	}
	int w, h;
	SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
	SDL_Rect dst = { x - _transX, y - _transY, w, h };
	SDL_RenderCopyEx(_renderer, texture, &src, &dst, angle, nullptr, SDL_FLIP_NONE);
}

void Graphics::drawTexture(SDL_Texture* texture, const int x, const int y, const double angle)
{
	if (!texture)
	{
		return;
	}
	int w, h;
	SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
	SDL_Rect dst = { x - _transX, y - _transY, w, h };
	SDL_RenderCopyEx(_renderer, texture, nullptr, &dst, angle, nullptr, SDL_FLIP_NONE);
}

void Graphics::drawTexture(SDL_Texture* texture, const double angle)
{
	if (!texture)
	{
		return;
	}
	SDL_Rect actRect = { -_transX, -_transY, _width, _height };
	SDL_RenderCopyEx(_renderer, texture, nullptr, &actRect, angle, nullptr, SDL_FLIP_NONE);
}

void Graphics::drawText(const int x, const int y, TTF_Font* font, const std::string& text, const double angle, const int renderType)
{
	switch (renderType)
	{
		case TEXT_RENDER_DYNAMIC:
			drawDynamicText(x, y, font, text, angle);
			break;
		case TEXT_RENDER_STATIC:
			drawStaticText(x, y, font, text, angle);
			break;
	}
}

void Graphics::drawText(const int x, const int y, TTF_Font* font, const std::string& text, const int renderType)
{
	drawText(x, y, font, text, 0, renderType);
}

void Graphics::drawStaticText(const int x, const int y, TTF_Font* font, const std::string& text, const double angle = 0)
{
	if(!font)
	{
		return;
	}
	SDL_Texture* texture;
	if (_textures.find(text) == _textures.end())
	{
		SDL_Surface* surf = TTF_RenderText_Solid(font, text.c_str(), _drawColor);
		texture = SDL_CreateTextureFromSurface(_renderer, surf);
		_textures[text] = texture;
		SDL_FreeSurface(surf);
	}
	else
	{
		texture = _textures[text];
	}
	drawTexture(texture, x, y, angle);
}

void Graphics::drawDynamicText(const int x, const int y, TTF_Font* font, const std::string& text, const double angle = 0)
{
	if (!font)
	{
		return;
	}
	SDL_Surface* surf = TTF_RenderText_Solid(font, text.c_str(), _drawColor);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, surf);
	SDL_FreeSurface(surf);
	drawTexture(texture, x, y, angle);
	SDL_DestroyTexture(texture);
}

void Graphics::drawPoint(const int x, const int y)
{
	SDL_RenderDrawPoint(_renderer, x - _transX, y - _transY);
}

void Graphics::drawLine(const int x1, const int y1, const int x2, const int y2)
{
	SDL_RenderDrawLine(_renderer, x1 - _transX, y1 - _transY, x2 - _transX, y2 - _transY);
}

void Graphics::drawFilledRect(const SDL_Rect& rect)
{
	SDL_Rect actRect = { rect.x - _transX, rect.y - _transY, rect.w, rect.h };
	SDL_RenderFillRect(_renderer, &actRect);
}

void Graphics::drawRectOutline(const SDL_Rect& rect)
{
	SDL_Rect actRect = { rect.x - _transX, rect.y - _transY, rect.w, rect.h };
	SDL_RenderDrawRect(_renderer, &actRect);
}

void Graphics::update()
{
	SDL_RenderPresent(_renderer);
}

void Graphics::translate(const int x, const int y)
{
	_transX += x;
	_transY += y;
}

void Graphics::resetTransformation()
{
	_transX = 0;
	_transY = 0;
}
