#include "MiniMap.h"

#include "Deserializers/Deserializers.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Deserializers/LayerDeserializer.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Terrain/TerrainObject.h"
#include "Engine/UI/SmartClippingNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Maps/GameMap.h"
#include "Entities/Platformer/Squally/Squally.h"

using namespace cocos2d;

const float MiniMap::MiniMapScale = 0.075f;
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
	this->squally = nullptr;
	this->miniMapTerrainObjects = std::map<TerrainObject*, float>();

	this->addLayerDeserializers({
			ObjectLayerDeserializer::create({
				{ MiniMapTerrainDeserializer::MapKeyTypeTerrain, MiniMapTerrainDeserializer::create() },
			})
		}
	);

	this->mapNode->setScale(MiniMap::MiniMapScale);
	
	this->addChild(this->mapClip);
	this->addChild(this->contentNode);
}

MiniMap::~MiniMap()
{
}

void MiniMap::onEnter()
{
	super::onEnter();

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
		this->squallyMap = GameUtils::getFirstParentOfType<GameMap>(this->squally);
	}, Squally::MapKey);

	this->miniMapTerrainObjects.clear();
	
	ObjectEvents::QueryObjects(QueryObjectsArgs<TerrainObject>([=](TerrainObject* terrainObject)
	{
		// All layers are forced to a depth of 0.0f, but we cache the original depth
		this->miniMapTerrainObjects[terrainObject] = GameUtils::getDepthUntil<GameMap>(terrainObject);

		terrainObject->setPositionZ(0.0f);
		terrainObject->detachAllBehavior();
		
	}), TerrainObject::TagMiniMapTerrain);
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

	this->positionMiniMap();
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

void MiniMap::positionMiniMap()
{
	this->mapNode->setPosition(-GameCamera::getInstance()->getCameraPosition() * MiniMap::MiniMapScale);

	float squallyDepth = GameUtils::getDepthUntil<GameMap>(this->squally);

	for (auto next : this->miniMapTerrainObjects)
	{
		TerrainObject* terrain = next.first;
		float depth = next.second;

		terrain->setVisible(std::abs(depth - squallyDepth) <= CollisionObject::CollisionZThreshold);
	}
}
