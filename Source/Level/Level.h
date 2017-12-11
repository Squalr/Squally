#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "GUI/Menus/PauseMenu.h"
#include "Collision/TileCollision.h"
#include "Entities/Player.h"

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

	Layer * environmentLayer;

	Player * player;
	Sprite * backGround;
	PauseMenu * pauseMenu;

private:
	void LoadLevel();
	void InitializeListeners();
	void OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
};

