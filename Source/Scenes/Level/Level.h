#pragma once
#include "cocos2d.h"

#include "Engine/Input/InputManager.h"
#include "Entities/Player/Player.h"
#include "Events/NavigationEvents.h"
#include "Events/PauseEvents.h"
#include "Engine/Maps/SerializableMap.h"
#include "Engine/Rendering/Components/FadeScene.h"
#include "Engine/Rendering/Components/InfiniteParallaxNode.h"
#include "Engine/Rendering/Components/Mouse.h"
#include "Engine/Rendering/Components/UILayer.h"
#include "Engine/Rendering/HUD/DeveloperHud.h"
#include "Engine/Rendering/HUD/HackerModeHud.h"
#include "Engine/Rendering/HUD/Hud.h"
#include "Engine/Rendering/Shaders/PostProcess.h"
#include "Resources.h"
#include "Scenes/Level/Environments/Backgrounds/MatrixRain/MatrixRain.h"
#include "Scenes/Menus/Dialog/DialogMenu.h"
#include "Scenes/Menus/Pause/PauseMenu.h"
#include "Utils/GameUtils.h"

#include "LevelCamera.h"

using namespace cocos2d;

// Forward declarations
class SerializableMap;

class Level : public FadeScene
{
public:
	static Level* create();

	void loadLevel(SerializableMap* levelMap);

protected:
	Level();
	~Level();

private:
	void initializePositions();
	void initializeListeners();
	void enableHackerMode();
	void disableHackerMode();
	void toggleDeveloperMode();
	void onMouseWheelScroll(EventMouse* event);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
	virtual void resume(void) override;
	void update(float) override;
	void onEnter() override;

	Node* mapNode;
	SerializableMap* map;
	Sprite* hackerModeBackground;
	MatrixRain * hackerModeRain;
	PostProcess* hackerModePostProcessGlow;
	PostProcess* gamePostProcessInversion;
	PostProcess* gamePostProcessNightVision;

	UILayer* mouseLayer;
	Hud* hud;
	DeveloperHud* developerHud;
	HackerModeHud* hackerModeHud;
	Mouse* mouse;

	LevelCamera* camera;

	static bool hackerMode;
	static bool developerMode;
};
