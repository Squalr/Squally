#pragma once
#include "cocos2d.h"
#include "../Entities/Player.h"
#include "../GUI/Menus/PauseMenu.h"

using namespace cocos2d;

class Level : public Scene
{
public:
	Level();
	~Level();

protected:
	Player * player;
	Sprite * backGround;
	PauseMenu * pauseMenu;

private:
	void InitializeListeners();
	void OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
};

