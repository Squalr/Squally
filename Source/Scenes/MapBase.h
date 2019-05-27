#pragma once

#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/GlobalScene.h"

namespace cocos2d
{
	class EventMouse;
	class Sprite;
	class Value;
	typedef std::map<std::string, Value> ValueMap;
}

class CodeEditor;
class ConfirmationMenu;
class DeveloperHud;
class Hud;
class OptionsMenu;
class PauseMenu;
class RadialMenu;
class SerializableMap;
class MatrixRain;
class HackerModeHud;

class MapBase : public GlobalScene
{
public:
	virtual void loadMap(std::string mapResource, std::vector<std::string> args = { });

	std::vector<std::string> getMapArgs();

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

	std::vector<std::string> mapArgs;

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
	CodeEditor* codeEditor;
	RadialMenu* radialMenu;
	PauseMenu* pauseMenu;
	OptionsMenu* optionsMenu;
	ConfirmationMenu* confirmationMenu;

	cocos2d::Node* mapNode;
	bool allowHackerMode;

	static bool hackerMode;
};
