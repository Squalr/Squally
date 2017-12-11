#include "Game.h"

Game::Game()
{
	this->titleScreen = new TitleScreen();

	Director::getInstance()->runWithScene(this->titleScreen);
}

Game::~Game()
{
	delete(this->titleScreen);
}
