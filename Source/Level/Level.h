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

	void onEnter() override;
	void update(float) override;

protected:
	Layer * backGroundLayer;
	Layer * tileLayer;

	Layer * entityLayer;
	Layer * playerLayer;
	Layer * enemyLayer;

	Player * player;
	Sprite * backGround;
	PauseMenu * pauseMenu;

private:
	void LoadLevel();
	void InitializeListeners();
	void OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
};

