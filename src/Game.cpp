#include "../include/Game.hpp"
#include <fstream>
#include <iostream>
#include <cmath>


const std::string Game::readFile(const std::string& file)
{
	std::ifstream in(file);
	if(in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize((unsigned)in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return contents;
	}
	return "";
}

Game::Game(Graphics* graphics, Input* input) :
	_graphics(graphics),
	_input(input),
	_start(false),
	_paddle(graphics),
	_ball(graphics),
	_MAX_LIVES(3),
	_SCORE_INC(50),
	_FONT("res/fonts/ttf-bitstream-vera-1.10/Vera.ttf")
{
	reset();
}

void Game::update()
{
	if (_input->isKeyDown(SDL_SCANCODE_LEFT))
	{
		_paddle.moveLeft();
		startBallIfNeeded();
	}
	if (_input->isKeyDown(SDL_SCANCODE_RIGHT))
	{
		_paddle.moveRight();
		startBallIfNeeded();
	}
	_ball.update();
	if (_ball.collidesWithPaddle(_paddle))
	{
		_ball.bounceOffPaddle(_paddle);
	}
	auto itr = _blocks.begin();
	while(itr != _blocks.end())
	{
		if(_ball.collidesWithBlock(*itr))
		{
			itr = _blocks.erase(itr);
			_score += _SCORE_INC;
		}
		else
		{
			itr++;
		}
	}
	if(_blocks.size() == 0)
	{
		_level++;
		loadLevel(_level);
		_ball.reset();
		_paddle.reset();
	}
	if(_ball.fellOffScreen())
	{
		_lives--;
		_ball.reset();
		_paddle.reset();
	}
	if(_lives == 0)
	{
		reset();
	}
}

void Game::render()
{
	_paddle.render();
	_ball.render();
	_graphics->translate(-_blockOffset, 0);
	for(auto& block : _blocks)
	{
		block.render();
	}
	_graphics->resetTransformation();
	_graphics->setDrawColor(Color::RED);
	const std::string scoreTxt = std::to_string(_score);
	_graphics->drawText(50, _graphics->getHeight() - 50, _graphics->loadFont(_FONT), "Score:", TEXT_RENDER_STATIC);
	_graphics->drawText(150, _graphics->getHeight() - 50, _graphics->loadFont(_FONT), scoreTxt, TEXT_RENDER_DYNAMIC);
	const std::string livesTxt = std::to_string(_lives);
	_graphics->drawText(_graphics->getWidth() - 170, _graphics->getHeight() - 50, _graphics->loadFont(_FONT), "Lives:", TEXT_RENDER_STATIC);
	_graphics->drawText(_graphics->getWidth() - 70, _graphics->getHeight() - 50, _graphics->loadFont(_FONT), livesTxt, TEXT_RENDER_DYNAMIC);
	_graphics->setDrawColor(Color::BLACK);
}

void Game::loadLevel(const int level)
{
	const std::string file = "levels/" + std::to_string(level) + ".txt";
	readLevel(file);
}

void Game::readLevel(const std::string& file)
{
	_blocks.clear();
	const std::string contents = readFile(file);
	if(contents == "")
	{
		return;
	}
	const int levelWidth = contents.find_first_of("\n");
	const int levelHeight = (int)std::floor(contents.size() / levelWidth);
	const int blockWidth = _graphics->getWidth() / levelWidth;
	const int blockHeight = (_graphics->getHeight() / 2) / levelHeight;
	_blockOffset = (_graphics->getWidth() - levelWidth * blockWidth) / 2;
	int pos = 0;
	std::string oneLongStr;
	for(auto const& itr : contents)
	{
		if(itr != '\n' && itr != ' ')
		{
			oneLongStr.push_back(itr);
		}
	}
	for(size_t i = 0; i < oneLongStr.size(); i++)
	{
		if(oneLongStr[i] == '1')
		{
			const int y = (int)std::floor(i / levelWidth);
			const int x = i - levelWidth * y;
			const int w = blockWidth;
			const int h = blockHeight;
			Block block(_graphics, w * x, h * y, w, h);
			_blocks.push_back(block);
		}
	}
}

void Game::reset()
{
	_paddle.reset();
	_ball.reset();
	_lives = _MAX_LIVES;
	_score = 0;
	_level = 1;
	loadLevel(_level);
}

void Game::startBallIfNeeded()
{
	if (!_ball.hasStarted())
	{
		_ball.start();
	}
}