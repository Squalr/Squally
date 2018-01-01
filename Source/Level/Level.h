#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Level/LevelCamera.h"
#include "Level/LevelParser.h"
#include "Entities/Player/Player.h"
#include "Input/InputManager.h"
#include "Utils/Utils.h"
#include "GUI/HUD/HUD.h"
#include "GUI/Components/FadeScene.h"
#include "GUI/Components/InfiniteParallaxNode.h"
#include "GUI/Menus/Pause/PauseMenu.h"

using namespace cocos2d;

class Level : public FadeScene
{
public:
	static Level* create(std::string levelResourceFilePath);

protected:
	Level(std::string levelResourceFilePath);
	~Level();

	void update(float) override;

private:
	void initializeListeners();
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	Layer * background;
	Layer * backgroundLayer;
	Layer * midgroundLayer;
	Layer * objectLayer;
	Layer * collisionLayer;
	Layer * foregroundLayer;
	Layer * environmentLayer;
	HUD * hud;

	Size mapSize;
};
