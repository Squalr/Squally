#pragma once

#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/GlobalScene.h"

// Forward declarations
class ConfirmationMenu;
class DeveloperHud;
class Hud;
class OptionsMenu;
class PauseMenu;
class SerializableMap;
class MatrixRain;
class HackerModeHud;

namespace cocos2d
{
	class EventMouse;
	class Sprite;
}

class MapBase : public GlobalScene
{
public:
	virtual void loadMap(SerializableMap* levelMap);

protected:
	MapBase();
	~MapBase();

	virtual void onEnter() override;
	virtual void resume() override;
	virtual void initializeListeners() override;
	virtual void onDeveloperModeEnable() override;
	virtual void onDeveloperModeDisable() override;
	virtual void onHackerModeEnable();
	virtual void onHackerModeDisable();
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onMouseWheelScroll(cocos2d::EventMouse* event);

private:
	void toggleHackerMode();
	void onOptionsExit();
	void openPauseMenu();
	void onResumeClick();
	void onOptionsClick();
	void onExitClick();

	Hud* hackerModeGlow;
	MatrixRain* hackerModeRain;
	HackerModeHud* hackerModeHud;
	DeveloperHud* developerHud;
	Hud* menuBackDrop;
	Hud* hud;
	PauseMenu* pauseMenu;
	OptionsMenu* optionsMenu;
	ConfirmationMenu* confirmationMenu;

	cocos2d::Node* mapNode;

	SerializableMap* map;

	static bool hackerMode;
};
