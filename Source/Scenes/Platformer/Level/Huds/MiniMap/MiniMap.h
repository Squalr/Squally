#pragma once

#include "Engine/UI/HUD/Hud.h"

namespace cocos2d
{
	class DrawNode;

	namespace cocos_experimental
	{
		class TMXTiledMap;
	};
};

class Inventory;
class LayerDeserializer;
class MiniGameMap;
class MiniMapObject;
class MiniMapTerrainObject;
class SmartClippingNode;
class Squally;

class MiniMap : public Hud
{
public:
	static MiniMap* create();

	void show(bool instant = false);
	void hide(bool instant = false);
	void setPositioning(std::string miniMapPositioning = "");
	bool loadMapFromTmx(std::string mapResource, cocos2d::cocos_experimental::TMXTiledMap* mapRaw);

protected:
	MiniMap();
	virtual ~MiniMap();
	
	void onHackerModeEnable() override;
	void onHackerModeDisable() override;
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;

	void addLayerDeserializer(LayerDeserializer* layerDeserializer);
	void addLayerDeserializers(std::vector<LayerDeserializer*> layerDeserializers);

	cocos2d::Node* rootNode = nullptr;
	cocos2d::Node* cinematicNode = nullptr;
	cocos2d::DrawNode* background = nullptr;
	cocos2d::Node* mapNode = nullptr;
	MiniGameMap* map = nullptr;
	cocos2d::DrawNode* squallyMarker = nullptr;
	SmartClippingNode* mapClip = nullptr;

	std::string mapResource;

private:
	typedef Hud super;

	void initializeMapData();
	void positionMiniMap();
	void positionEntityIcons();

	Squally* squally = nullptr;
	MiniGameMap* squallyMap = nullptr;
	cocos2d::Node* contentNode = nullptr;

	std::vector<LayerDeserializer*> layerDeserializers;
	std::map<MiniMapTerrainObject*, float> miniMapTerrainObjects;
	std::map<MiniMapObject*, float> miniMapObjects;
	
	bool isShown = false;

	static const float MiniMapScale;
	static const cocos2d::CSize MiniMapSize;
	static const cocos2d::Vec2 MiniMapMargin;
};
