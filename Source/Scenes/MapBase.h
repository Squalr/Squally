#pragma once

#include "Engine/GlobalScene.h"

namespace cocos2d
{
	class Sprite;
	class Value;
	typedef std::map<std::string, Value> ValueMap;

	namespace cocos_experimental
	{
		class TMXTiledMap;
	}
}

class CodeHud;
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
	bool loadMap(std::string mapResource);

protected:
	MapBase(bool useIngameMenu, bool allowHackerMode);
	virtual ~MapBase();

	void onEnter() override;
	void initializeListeners() override;
	void onDeveloperModeEnable(int debugLevel) override;
	void onDeveloperModeDisable() override;
	void onHackerModeEnable() override;
	void onHackerModeDisable() override;
	void addLayerDeserializer(LayerDeserializer* layerDeserializer);
	void addLayerDeserializers(std::vector<LayerDeserializer*> layerDeserializers);
	void openPauseMenu(cocos2d::Node* refocusTarget);
	virtual bool loadMapFromTmx(std::string mapResource, cocos2d::cocos_experimental::TMXTiledMap* mapRaw);

	cocos2d::Node* hudNode;
	Hud* hud;
	Hud* hackerModeVisibleHud;
	Hud* miniGameHud;
	Hud* backMenuHud;
	Hud* menuBackDrop;
	Hud* menuHud;
	Hud* topMenuHud;
	Hud* confirmationMenuHud;
	IngameMenu* ingameMenu;
	PauseMenu* pauseMenu;
	cocos2d::Node* mapNode;
	GameMap* map;

	bool canPause;
	bool allowHackerMode;
	std::string mapResource;
	std::vector<std::string> mapArgs;

private:
	typedef GlobalScene super;
	void toggleHackerMode(void* userData);

	Hud* hackerModeGlow;
	MatrixRain* hackerModeRain;
	CodeHud* codeHud;
	RadialMenu* radialMenu;
	OptionsMenu* optionsMenu;
	MusicOverlay* musicOverlay;

	std::vector<LayerDeserializer*> layerDeserializers;
};
