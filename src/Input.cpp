#include "../include/Input.hpp"


Input::Input():
	_shouldQuit(false)
{
	resetKeys();
}

void Input::update()
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		if(e.type == SDL_QUIT)
		{
			_shouldQuit = true;
		}
	}
	if(isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		_shouldQuit = true;		
	}
}

void Input::resetKeys()
{
	_keys = SDL_GetKeyboardState(NULL);
}

const int Input::getMousePosX()
{
	int x;
	SDL_GetMouseState(&x, NULL);
	return x;
}

const int Input::getMousePosY()
{
	int y;
	SDL_GetMouseState(NULL, &y);
	return y;
}
