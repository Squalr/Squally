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
	void loadMap(std::string mapResource);

protected:
	MapBase(bool allowHackerMode);
	~MapBase();

	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void resume() override;
	void initializeListeners() override;
	void onDeveloperModeEnable() override;
	void onDeveloperModeDisable() override;
	virtual void onHackerModeEnable();
	virtual void onHackerModeDisable();
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onMouseWheelScroll(cocos2d::EventMouse* event);

	cocos2d::Node* hudNode;
	Hud* hud;
	Hud* menuBackDrop;
	Hud* menuHud;
	SerializableMap* map;

private:
	typedef GlobalScene super;
	void toggleHackerMode();
	void onOptionsExit();
	void openPauseMenu();
	void onResumeClick();
	void onOptionsClick();
	void onExitClick();

	Hud* hackerModeGlow;
	MatrixRain* hackerModeRain;
	PauseMenu* pauseMenu;
	OptionsMenu* optionsMenu;
	ConfirmationMenu* confirmationMenu;

	cocos2d::Node* mapNode;

	bool allowHackerMode;
	static bool hackerMode;
};
