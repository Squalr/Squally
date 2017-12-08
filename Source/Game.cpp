#include "Game.h"
#include "SimpleAudioEngine.h"
#include "Resources.h"
#include "GUI/Screens/TitleScreen.h"
#include "Level/Level.h"

using namespace cocos2d;

Game::Game()
{
	this->titleScreen = new TitleScreen(bind(&Game::GameStart, this));

	// Show level
	Director::getInstance()->runWithScene(this->titleScreen);
}

Game::~Game()
{
	delete(this->titleScreen);
}

void Game::GameStart()
{
	Level* level = new Level();

	Director::getInstance()->replaceScene(level);
}
