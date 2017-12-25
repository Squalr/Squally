#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Background.h"
#include "Collision/TileCollision.h"
#include "Entities/Player.h"
#include "Input/InputManager.h"
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

	Layer * entityLayer;
	Layer * playerLayer;
	Layer * enemyLayer;

	Layer * environmentLayer;

	Player * player;

private:
	void LoadLevel(std::string levelResourceFilePath);
	void InitializeListeners();
	void OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	const float cameraOffsetX = 128.0f;
	const float cameraOffsetY = 96.0f;
};

