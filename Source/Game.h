#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "GUI/Screens/TitleScreen.h"
#include "Level/Level.h"

using namespace cocos2d;

class Game
{
public:
	Game();
	~Game();

private:
	TitleScreen * titleScreen;
};
