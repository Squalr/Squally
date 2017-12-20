#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Background.h"
#include "GUI/Menus/Pause/PauseMenu.h"
#include "Collision/TileCollision.h"
#include "Entities/Player.h"
#include "Utils/InfiniteParallaxNode.h"

using namespace cocos2d;

class Level : public Scene
{
public:
	static Level* create(std::string levelResourceFilePath);

protected:
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

private:
	void LoadLevel(std::string levelResourceFilePath);
	void InitializeListeners();
	void OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
};

