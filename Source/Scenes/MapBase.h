#pragma once

#include "Engine/GlobalScene.h"

namespace cocos2d
{
	class Sprite;
	class Value;
	typedef std::map<std::string, Value> ValueMap;
}

class CodeHud;
class ConfirmationMenu;
class DeveloperHud;
class GameMap;
class Hud;
class IngameMenu;
class LayerDeserializer;
class MatrixRain;
class MusicOverlay;
class OptionsMenu;
class PauseMenu;
class PlatformerDialogueBox;
class RadialMenu;
class HackerModeHud;

class MapBase : public GlobalScene
{
public:
	virtual bool loadMap(std::string mapResource);

protected:
	MapBase(bool useIngameMenu, bool allowHackerMode);
	virtual ~MapBase();

	void onEnter() override;
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

	cocos2d::Node* mapNode;

private:
	typedef GlobalScene super;
	void toggleHackerMode(void* userData);

	Hud* hackerModeGlow;
	Hud* sensingGlow;
	MatrixRain* hackerModeRain;
	CodeHud* codeHud;
	RadialMenu* radialMenu;
	OptionsMenu* optionsMenu;
	ConfirmationMenu* confirmationMenu;
	MusicOverlay* musicOverlay;

	std::vector<LayerDeserializer*> layerDeserializers;
};
