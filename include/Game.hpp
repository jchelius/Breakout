#ifndef GAME_H
#define GAME_H

#include "../include/Graphics.hpp"
#include "../include/Input.hpp"
#include "../include/Paddle.hpp"
#include "../include/Ball.hpp"
#include "../include/Block.hpp"

#include <vector>


class Game
{
private:
	Input* _input;
	Graphics* _graphics;
	bool _start;
	Paddle _paddle;
	Ball _ball;
	int _level;
	std::vector<Block> _blocks;
	int _lives;
	int _score;
	int _blockOffset;
	const int _MAX_LIVES, _SCORE_INC;
	const std::string _FONT;
public:
	Game(Graphics* graphics, Input* input);
	~Game() { }
	void update();
	void render();
private:
	const std::string readFile(const std::string& file);
	void loadLevel(const int level);
	void readLevel(const std::string& file);
	void reset();
	void startBallIfNeeded();
};


#endif //GAME_H