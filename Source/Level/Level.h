#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "GUI/Menus/PauseMenu.h"
#include "Collision/TileCollision.h"
#include "Entities/Player.h"
#include "Utils/InfiniteParallaxNode.h"

using namespace cocos2d;

class Level : public Scene
{
public:
	Level(std::string levelResourceFilePath);
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
	InfiniteParallaxNode * clouds;
	ParallaxNode * mountains;
	ParallaxNode * mountains2;
	ParallaxNode * trees1;
	ParallaxNode * trees2;
	ParallaxNode * trees3;
	PauseMenu * pauseMenu;

private:
	void LoadLevel(std::string levelResourceFilePath);
	void InitializeListeners();
	void OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
};

