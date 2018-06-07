#pragma once
#include "cocos2d.h"

#include "Engine/Input/InputManager.h"
#include "Entities/Player/Player.h"
#include "Events/NavigationEvents.h"
#include "Events/PauseEvents.h"
#include "Engine/Rendering/Components/FadeScene.h"
#include "Engine/Rendering/Components/InfiniteParallaxNode.h"
#include "Engine/Rendering/Components/Mouse.h"
#include "Engine/Rendering/Components/UILayer.h"
#include "Engine/Rendering/HUD/HackerModeHud.h"
#include "Engine/Rendering/HUD/Hud.h"
#include "Engine/Rendering/Shaders/PostProcess.h"
#include "Resources.h"
#include "Scenes/Menus/Dialog/DialogMenu.h"
#include "Scenes/Menus/Pause/PauseMenu.h"
#include "Utils/GameUtils.h"

#include "Backgrounds/MatrixRain/MatrixRain.h"
#include "LevelCamera.h"
#include "LevelMap.h"

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
