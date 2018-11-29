#pragma once
#include "cocos2d.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Maps/SerializableMap.h"
#include "Engine/Shaders/PostProcess.h"
#include "Engine/UI/FadeScene.h"
#include "Engine/UI/InfiniteParallaxNode.h"
#include "Engine/UI/HUD/DeveloperHud.h"
#include "Engine/UI/HUD/HackerModeHud.h"
#include "Engine/UI/HUD/Hud.h"
#include "Engine/UI/Mouse.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/NavigationEvents.h"
#include "Menus/Confirmation/ConfirmationMenu.h"
#include "Menus/Dialog/DialogMenu.h"
#include "Menus/Options/OptionsMenu.h"
#include "Menus/Pause/PauseMenu.h"
#include "Resources/BackgroundResources.h"
#include "Resources/ShaderResources.h"
#include "Scenes/Maps/IMap.h"
#include "Scenes/Maps/Platformer/Backgrounds/MatrixRain/MatrixRain.h"

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
	void initializePositions() override;
	void initializeListeners() override;
	void toggleHackerMode();
	void toggleDeveloperMode();
	void onMouseWheelScroll(EventMouse* event);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
	virtual void resume(void) override;
	void update(float) override;
	void onEnter() override;
	void onOptionsExit();
	void openPauseMenu();
	void onResumeClick();
	void onOptionsClick();
	void onExitClick();

	Node* mapNode;
	SerializableMap* map;
	Sprite* hackerModeBackground;
	MatrixRain * hackerModeRain;
	PostProcess* hackerModePostProcessGlow;
	PostProcess* gamePostProcessInversion;
	PostProcess* gamePostProcessNightVision;

	Node* mouseLayer;
	Hud* hud;
	DeveloperHud* developerHud;
	HackerModeHud* hackerModeHud;

	LayerColor* menuBackDrop;
	PauseMenu* pauseMenu;
	OptionsMenu* optionsMenu;
	ConfirmationMenu* confirmationMenu;

	GameCamera* camera;

	static bool hackerMode;
	static bool developerMode;
};
