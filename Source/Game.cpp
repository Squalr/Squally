#include "Game.h"

Game::Game()
{
	Director::getInstance()->runWithScene(TitleScreen::create());
}

Game::~Game()
{
}
