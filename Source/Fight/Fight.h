#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Level/Backgrounds/MatrixRain/MatrixRain.h"
#include "Level/LevelCamera.h"
#include "Level/Parser/Parser.h"
#include "Entities/Entities.h"
#include "Input/InputManager.h"
#include "Utils/GameUtils.h"
#include "Shaders/PostProcess.h"
#include "GUI/HUD/Hud.h"
#include "GUI/HUD/HackerModeHud.h"
#include "GUI/Components/FadeScene.h"
#include "GUI/Components/InfiniteParallaxNode.h"
#include "GUI/Components/Mouse.h"
#include "GUI/Menus/Dialog/DialogMenu.h"
#include "GUI/Menus/Pause/PauseMenu.h"

using namespace cocos2d;

class Fight : public FadeScene
{
public:
	static Fight* create();

	void loadFight(Player* player, Enemy* enemy);

protected:
	Fight();
	~Fight();

private:
	void onEnter() override;
	void update(float) override;
	void initializePositions();
	void initializeListeners();

	Layer * background;
	Layer * entityLayer;
	Layer * objectLayer;
};
