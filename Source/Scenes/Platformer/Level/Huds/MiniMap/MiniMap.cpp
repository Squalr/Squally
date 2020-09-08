#include "MiniMap.h"

#include "Deserializers/Deserializers.h"
#include "Engine/Deserializers/LayerDeserializer.h"
#include "Engine/UI/SmartClippingNode.h"
#include "Engine/Maps/GameMap.h"

using namespace cocos2d;

const Size MiniMap::MiniMapSize = Size(320.0f, 224.0f);
const Vec2 MiniMap::MiniMapMargin = Vec2(32.0f, 32.0f);

MiniMap* MiniMap::create()
{
	MiniMap* instance = new MiniMap();

	instance->autorelease();

	return instance;
}

MiniMap::MiniMap()
{
	this->contentNode = Node::create();
	this->layerDeserializers = std::vector<LayerDeserializer*>();
	this->mapNode = Node::create();
	this->contentNode = Node::create();
	this->mapClip = SmartClippingNode::create(this->mapNode, MiniMap::MiniMapSize);
	this->map = nullptr;
	this->mapResource = "";

	this->addLayerDeserializers({
			ObjectLayerDeserializer::create({
				{ MiniMapTerrainDeserializer::MapKeyTypeTerrain, MiniMapTerrainDeserializer::create() },
			})
		}
	);

	this->mapNode->setScale(0.1f);
	
	this->addChild(this->mapClip);
	this->addChild(this->contentNode);
}

MiniMap::~MiniMap()
{
}

void MiniMap::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	const Vec2 Offset = Vec2(visibleSize - MiniMapSize) / 2.0f - MiniMapMargin;

	this->mapClip->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f) + Offset);
	this->contentNode->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f) + Offset);
}

void MiniMap::initializeListeners()
{
	super::initializeListeners();
}

void MiniMap::update(float dt)
{
	super::update(dt);
}

bool MiniMap::loadMap(std::string mapResource)
{
	if (this->map != nullptr)
	{
		this->mapNode->removeChild(this->map);
	}

	this->mapResource = mapResource;
	this->map = GameMap::deserialize(this->mapResource, this->layerDeserializers, true, true);
	
	if (this->map != nullptr)
	{
		this->mapNode->addChild(this->map);
		// GameCamera::getInstance()->setMapBounds(Rect(0.0f, 0.0f, this->map->getMapSize().width, this->map->getMapSize().height));

		return true;
	}

	return false;
}

void MiniMap::addLayerDeserializer(LayerDeserializer* layerDeserializer)
{
	this->addChild(layerDeserializer);
	this->layerDeserializers.push_back(layerDeserializer);
}

void MiniMap::addLayerDeserializers(std::vector<LayerDeserializer*> layerDeserializers)
{
	for (auto next : layerDeserializers)
	{
		this->addChild(next);
		this->layerDeserializers.push_back(next);
	}
}
