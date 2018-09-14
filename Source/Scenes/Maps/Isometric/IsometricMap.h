#pragma once
#include "cocos2d.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Maps/SerializableMap.h"
#include "Engine/Shaders/PostProcess.h"
#include "Engine/UI/Mouse.h"
#include "Engine/UI/FadeScene.h"
#include "Engine/UI/InfiniteParallaxNode.h"
#include "Engine/UI/HUD/DeveloperHud.h"
#include "Engine/UI/HUD/HackerModeHud.h"
#include "Engine/UI/HUD/Hud.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Isometric/Squally/IsometricSqually.h"
#include "Events/NavigationEvents.h"
#include "Resources.h"
#include "Scenes/Maps/IMap.h"
#include "Scenes/Maps/Platformer/Backgrounds/MatrixRain/MatrixRain.h"
#include "Scenes/Menus/Dialog/DialogMenu.h"
#include "Scenes/Menus/Pause/PauseMenu.h"

using namespace cocos2d;

// Forward declarations
class SerializableMap;

class IsometricMap : public IMap
{
public:
	static IsometricMap* create();

	void loadMap(SerializableMap* serializableMap) override;

protected:
	IsometricMap();
	~IsometricMap();

private:
	void initializePositions();
	void initializeListeners();
	void toggleHackerMode();
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

	Hud* mouseLayer;
	Hud* hud;
	DeveloperHud* developerHud;
	HackerModeHud* hackerModeHud;
	Mouse* mouse;

	GameCamera* camera;

	static bool hackerMode;
	static bool developerMode;
};
