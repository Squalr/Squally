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
	bool loadMap(std::string mapResource);

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
	virtual void openPauseMenu(cocos2d::Node* refocusTarget);
	virtual bool loadMapFromTmx(std::string mapResource, cocos2d::cocos_experimental::TMXTiledMap* mapRaw);

	cocos2d::Node* hudNode;
	Hud* hud;
	Hud* hackerModeVisibleHud;
	Hud* miniGameHud;
	Hud* backMenuHud;
	Hud* menuBackDrop;
	Hud* hackMenuHud;
	Hud* menuHud;
	Hud* topMenuHud;
	Hud* confirmationMenuHud;
	LazyNode<OptionsMenu>* optionsMenu;
	cocos2d::Node* mapNode;
	GameMap* map;

	bool canPause;
	bool allowHackerMode;
	std::string mapResource;
	std::vector<std::string> mapArgs;

private:
	typedef GlobalScene super;
	void toggleHackerMode(void* userData);
	CodeHud* buildCodeHud();
	RadialMenu* buildRadialMenu();
	OptionsMenu* buildOptionsMenu();

	Hud* hackerModeGlow;
	MatrixRain* hackerModeRain;
	LazyNode<CodeHud>* codeHud;
	LazyNode<RadialMenu>* radialMenu;
	MusicOverlay* musicOverlay;

	std::vector<LayerDeserializer*> layerDeserializers;

	static std::map<std::string, cocos2d::cocos_experimental::TMXTiledMap*> MapCache;
};
