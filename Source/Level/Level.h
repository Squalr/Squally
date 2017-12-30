#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Background.h"
#include "Collision/Collision.h"
#include "Level/LevelCamera.h"
#include "Entities/Player/Player.h"
#include "Entities/Enemies/Shroom.h"
#include "Input/InputManager.h"
#include "GUI/HUD/HUD.h"
#include "GUI/Components/FadeScene.h"
#include "GUI/Components/InfiniteParallaxNode.h"
#include "GUI/Menus/Pause/PauseMenu.h"
#include <algorithm> 

using namespace cocos2d;

class Level : public FadeScene
{
public:
	static Level* create(std::string levelResourceFilePath);

protected:
	Level(std::string levelResourceFilePath);
	~Level();

	void update(float) override;

protected:

	Layer * backGroundLayer;
	Layer * tileLayer;
	Layer * foregroundLayer;
	HUD * hud;

	Layer * entityLayer;
	Layer * playerLayer;
	Layer * enemyLayer;

	Layer * environmentLayer;

	Player * player;

private:
	void loadLevel(std::string levelResourceFilePath);
	void initializeListeners();
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
};

