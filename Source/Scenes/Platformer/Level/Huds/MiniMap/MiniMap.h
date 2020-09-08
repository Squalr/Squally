#pragma once

#include "Engine/UI/HUD/Hud.h"

namespace cocos2d
{
	class Sprite;
};

class GameMap;
class LayerDeserializer;
class LocalizedLabel;
class LocalizedString;
class SmartClippingNode;

class MiniMap : public Hud
{
public:
	static MiniMap* create();

	bool loadMap(std::string mapResource);

protected:
	MiniMap();
	virtual ~MiniMap();
	
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;

	void addLayerDeserializer(LayerDeserializer* layerDeserializer);
	void addLayerDeserializers(std::vector<LayerDeserializer*> layerDeserializers);

	cocos2d::Node* mapNode;
	GameMap* map;
	SmartClippingNode* mapClip;

	std::string mapResource;

private:
	typedef Hud super;

	cocos2d::Node* contentNode;

	std::vector<LayerDeserializer*> layerDeserializers;

	static const cocos2d::Size MiniMapSize;
	static const cocos2d::Vec2 MiniMapMargin;
};
