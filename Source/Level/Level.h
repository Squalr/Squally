#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Level/Backgrounds/MatrixRain/MatrixRain.h"
#include "Level/LevelCamera.h"
#include "Level/LevelMap.h"
#include "Entities/Player/Player.h"
#include "Input/InputManager.h"
#include "Events/NavigationEvents.h"
#include "Events/PauseEvents.h"
#include "Utils/GameUtils.h"
#include "Shaders/PostProcess.h"
#include "GUI/HUD/Hud.h"
#include "GUI/HUD/HackerModeHud.h"
#include "GUI/Components/FadeScene.h"
#include "GUI/Components/InfiniteParallaxNode.h"
#include "GUI/Components/Mouse.h"
#include "GUI/Components/UILayer.h"
#include "GUI/Menus/Dialog/DialogMenu.h"
#include "GUI/Menus/Pause/PauseMenu.h"

using namespace cocos2d;

// Forward declarations
class LevelMap;

class Level : public FadeScene
{
public:
	static Level* create();

	void loadLevel(LevelMap* levelMap);

protected:
	Level();
	~Level();

private:
	void initializePositions();
	void initializeListeners();
	void enableHackerMode();
	void disableHackerMode();
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
	virtual void resume(void) override;
	void update(float) override;
	void onEnter() override;

	Node* mapNode;
	LevelMap* map;
	Sprite* hackerModeBackground;
	MatrixRain * hackerModeRain;
	PostProcess* hackerModePostProcessGlow;
	PostProcess* gamePostProcessInversion;
	PostProcess* gamePostProcessNightVision;

	UILayer* uiLayer;
	Hud* hud;
	HackerModeHud* hackerModeHud;
	Mouse* mouse;
	LevelCamera* camera;

	static bool hackerMode;
};
