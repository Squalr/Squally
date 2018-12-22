#pragma once

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
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onMouseWheelScroll(EventMouse* event);

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

	Node* mapNode;
	Hud* mouseLayer;

	SerializableMap* map;

	static bool hackerMode;
};
