#pragma once

#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/GlobalScene.h"

// Forward declarations
class Cipher;
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

	void onEnter() override;
	void resume() override;
	void initializeListeners() override;
	void onDeveloperModeEnable() override;
	void onDeveloperModeDisable() override;
	virtual void onHackerModeEnable();
	virtual void onHackerModeDisable();
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onMouseWheelScroll(cocos2d::EventMouse* event);

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
	void openCipher();
	void onCipherClose();

	Hud* hackerModeGlow;
	MatrixRain* hackerModeRain;
	PauseMenu* pauseMenu;
	OptionsMenu* optionsMenu;
	Cipher* cipher;
	ConfirmationMenu* confirmationMenu;

	cocos2d::Node* mapNode;

	static bool hackerMode;
};
