#pragma once
#include "cocos2d.h"
#include "GUI/Screens/TitleScreen.h"
#include "Level/Level.h"

using namespace cocos2d;

class Game
{
public:
	Game();
	~Game();

	// A selector callback
	void menuCloseCallback(Ref* pSender);

private:
	void GameStart();

	TitleScreen * titleScreen;
};
