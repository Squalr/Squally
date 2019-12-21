#pragma once

#include "Engine/GlobalScene.h"

namespace cocos2d
{
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
	void onDeveloperModeEnable(int debugLevel) override;
	void onDeveloperModeDisable() override;
	void onHackerModeEnable(int hackFlags) override;
	void onHackerModeDisable() override;
	void addLayerDeserializer(LayerDeserializer* layerDeserializer);
	void addLayerDeserializers(std::vector<LayerDeserializer*> layerDeserializers);
	void openPauseMenu(cocos2d::Node* refocusTarget);

	cocos2d::Node* hudNode;
	Hud* hud;
	Hud* hackerModeVisibleHud;
	Hud* miniGameHud;
	Hud* menuBackDrop;
	Hud* menuHud;
	Hud* topMenuHud;
	IngameMenu* ingameMenu;
	PauseMenu* pauseMenu;
	GameMap* map;

	bool canPause;
	bool allowHackerMode;
	std::vector<std::string> mapArgs;

private:
	typedef GlobalScene super;
	void toggleHackerMode(void* userData);

	Hud* hackerModeGlow;
	Hud* sensingGlow;
	MatrixRain* hackerModeRain;
	CodeEditor* codeEditor;
	RadialMenu* radialMenu;
	OptionsMenu* optionsMenu;
	ConfirmationMenu* confirmationMenu;

	std::vector<LayerDeserializer*> layerDeserializers;

	cocos2d::Node* mapNode;
};
