#pragma once

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
class LayerDeserializer;
class OptionsMenu;
class PauseMenu;
class RadialMenu;
class GameMap;
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
	void onHackerModeEnable(int eq) override;
	void onHackerModeDisable() override;
	void onMouseWheelScroll(cocos2d::EventMouse* event);
	void addLayerDeserializer(LayerDeserializer* layerDeserializer);
	void addLayerDeserializers(std::vector<LayerDeserializer*> layerDeserializers);

	cocos2d::Node* hudNode;
	Hud* hud;
	Hud* hackerModeVisibleHud;
	Hud* menuBackDrop;
	Hud* menuHud;
	Hud* topMenuHud;
	PauseMenu* pauseMenu;
	GameMap* map;

	bool allowHackerMode;
	std::vector<std::string> mapArgs;

private:
	typedef GlobalScene super;
	void toggleHackerMode(void* userData);
	void onOptionsExit();
	void openPauseMenu();
	void onResumeClick();
	void onOptionsClick();
	void onExitClick();

	Hud* hackerModeGlow;
	MatrixRain* hackerModeRain;
	CodeEditor* codeEditor;
	RadialMenu* radialMenu;
	OptionsMenu* optionsMenu;
	ConfirmationMenu* confirmationMenu;

	std::vector<LayerDeserializer*> layerDeserializers;

	cocos2d::Node* mapNode;
};
