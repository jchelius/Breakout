#include "../include/Game.hpp"
#include "../include/Random.hpp"


const int WIDTH = 1000;
const int HEIGHT = 800;
const std::string TITLE = "Breakout";


int main(int, char**)
{
	Graphics* graphics = new Graphics(WIDTH, HEIGHT, TITLE);
	Input* input = new Input;
	Game game(graphics, input);
	while(!input->shouldQuit())
	{
		input->update();
		graphics->clear();
		game.update();
		game.render();
		graphics->update();
	}
	delete graphics;
	return 0;
}