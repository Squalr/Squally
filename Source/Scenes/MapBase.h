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
class IngameMenu;
class Hud;
class LayerDeserializer;
class OptionsMenu;
class PauseMenu;
class PlatformerDialogueBox;
class RadialMenu;
class GameMap;
class MatrixRain;
class HackerModeHud;

class MapBase : public GlobalScene
{
public:
	virtual bool loadMap(std::string mapResource);

protected:
	MapBase(bool useIngameMenu, bool allowHackerMode);
	~MapBase();

	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void resume() override;
	void initializePositions() override;
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
	IngameMenu* ingameMenu;
	PauseMenu* pauseMenu;
	GameMap* map;

	bool allowHackerMode;
	std::vector<std::string> mapArgs;

private:
	typedef GlobalScene super;
	void toggleHackerMode(void* userData);
	void openPauseMenu();

	Hud* hackerModeGlow;
	MatrixRain* hackerModeRain;
	PlatformerDialogueBox* dialogueBox;
	CodeEditor* codeEditor;
	RadialMenu* radialMenu;
	OptionsMenu* optionsMenu;
	ConfirmationMenu* confirmationMenu;

	std::vector<LayerDeserializer*> layerDeserializers;

	cocos2d::Node* mapNode;
};
