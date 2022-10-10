#pragma once

#include "cocos/base/CCValue.h"

#include "Engine/GlobalScene.h"

namespace cocos2d
{
	namespace cocos_experimental
	{
		class TMXTiledMap;
	}
}

class CodeHud;
class DeveloperHud;
class GameMap;
class Hud;
class LayerDeserializer;
template <class T> class LazyNode;
class MatrixRain;
class MusicOverlay;
class OptionsMenu;
class RadialMenu;

class MapBase : public GlobalScene
{
public:
	bool loadMap(std::string mapResource, bool useFallback = true);

protected:
	MapBase(bool allowHackerMode);
	virtual ~MapBase();

	void onEnter() override;
	void initializeListeners() override;
	void onDeveloperModeEnable(int debugLevel) override;
	void onDeveloperModeDisable() override;
	void onHackerModeEnable() override;
	void onHackerModeDisable() override;
	void addLayerDeserializer(LayerDeserializer* layerDeserializer);
	void addLayerDeserializers(std::vector<LayerDeserializer*> layerDeserializers);
	virtual cocos2d::Node* openPauseMenu(cocos2d::Node* refocusTarget);
	virtual bool loadMapFromTmx(std::string mapResource, cocos2d::cocos_experimental::TMXTiledMap* mapRaw, bool useFallback = true);

	cocos2d::Node* hudNode = nullptr;
	Hud* hud = nullptr;
	Hud* hackerModeVisibleHud = nullptr;
	Hud* miniGameHud = nullptr;
	Hud* backMenuHud = nullptr;
	Hud* menuBackDrop = nullptr;
	Hud* hackMenuHud = nullptr;
	Hud* menuHud = nullptr;
	Hud* topMenuHud = nullptr;
	Hud* confirmationMenuHud = nullptr;
	LazyNode<OptionsMenu>* optionsMenu = nullptr;
	cocos2d::Node* mapNode = nullptr;
	GameMap* map = nullptr;
	Node* pauseMenuRef = nullptr;

	bool canPause = false;
	bool allowHackerMode = false;
	bool hackerModeEnabled = false;
	std::string mapResource;
	std::vector<std::string> mapArgs;

private:
	typedef GlobalScene super;

	void toggleHackerMode(void* userData);
	CodeHud* buildCodeHud();
	RadialMenu* buildRadialMenu();
	OptionsMenu* buildOptionsMenu();
	
	Hud* hackerModeGlow = nullptr;
	MatrixRain* hackerModeRain = nullptr;
	LazyNode<CodeHud>* codeHud = nullptr;
	LazyNode<RadialMenu>* radialMenu = nullptr;
	MusicOverlay* musicOverlay = nullptr;

	std::vector<LayerDeserializer*> layerDeserializers;

	static std::map<std::string, cocos2d::cocos_experimental::TMXTiledMap*> MapCache;
};
