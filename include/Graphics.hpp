#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <map>
#include <vector>

#include "../include/Color.hpp"


enum TextRenderType
{
	TEXT_RENDER_STATIC,
	TEXT_RENDER_DYNAMIC,
};

class Graphics
{
private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	const int _width, _height;
	std::map<std::string, SDL_Texture*> _textures;
	std::map<std::pair<std::string, int>, TTF_Font*> _fonts;
	SDL_Color _drawColor;
private:
	void drawStaticText(const int x, const int y, TTF_Font* font, const std::string& text, const double angle);
	void drawDynamicText(const int x, const int y, TTF_Font* font, const std::string& text, const double angle);
public:
	Graphics(const int width, const int height, const std::string& title = "Game");
	~Graphics();
	const int getWidth() const { return _width; }
	const int getHeight() const { return _height; }
	void setDrawColor(const Color& color);
	void clear();
	SDL_Texture* loadTexture(const std::string& file);
	TTF_Font* loadFont(const std::string& file, const int size = 28);
	void drawTexture(SDL_Texture* texture, const SDL_Rect& src, const int x, const int y, const double angle = 0);
	void drawTexture(SDL_Texture* texture, const int x, const int y, const double angle = 0);
	void drawTexture(SDL_Texture* texture, const double angle = 0);
	void drawText(const int x, const int y, TTF_Font* font, const std::string& text, const int renderType = TEXT_RENDER_DYNAMIC);
	void drawText(const int x, const int y, TTF_Font* font, const std::string& text, const double angle, const int renderType = TEXT_RENDER_DYNAMIC);
	void drawPoint(const int x, const int y);
	void drawLine(const int x1, const int y1, const int x2, const int y2);
	void drawFilledRect(const SDL_Rect& rect);
	void drawRectOutline(const SDL_Rect& rect);
	void update();
};


#endif //GRAPHICS_H