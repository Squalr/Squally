#pragma once
#include "cocos2d.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Maps/SerializableMap.h"
#include "Engine/Rendering/Components/FadeScene.h"
#include "Engine/Rendering/Components/InfiniteParallaxNode.h"
#include "Engine/Rendering/Components/Mouse.h"
#include "Engine/Rendering/Components/UILayer.h"
#include "Engine/Rendering/HUD/DeveloperHud.h"
#include "Engine/Rendering/HUD/HackerModeHud.h"
#include "Engine/Rendering/HUD/Hud.h"
#include "Engine/Rendering/Shaders/PostProcess.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/NavigationEvents.h"
#include "Resources.h"
#include "Scenes/Maps/IMap.h"
#include "Scenes/Maps/Platformer/Backgrounds/MatrixRain/MatrixRain.h"
#include "Scenes/Menus/Dialog/DialogMenu.h"
#include "Scenes/Menus/Pause/PauseMenu.h"

using namespace cocos2d;

// Forward declarations
class SerializableMap;

class PlatformerMap : public IMap
{
public:
	static PlatformerMap* create();

	void loadMap(SerializableMap* serializableMap) override;

protected:
	PlatformerMap();
	~PlatformerMap();

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

	UILayer* mouseLayer;
	Hud* hud;
	DeveloperHud* developerHud;
	HackerModeHud* hackerModeHud;
	Mouse* mouse;

	GameCamera* camera;

	static bool hackerMode;
	static bool developerMode;
};
