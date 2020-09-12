#include "MiniMap.h"

#include "cocos/2d/CCDrawNode.h"

#include "Deserializers/Deserializers.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Deserializers/LayerDeserializer.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Terrain/MiniMapTerrainObject.h"
#include "Engine/UI/SmartClippingNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Maps/GameMap.h"
#include "Engine/Maps/MapLayer.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Objects/Platformer/MiniMap/MiniMapObject.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const float MiniMap::MiniMapScale = 0.065f;
const Size MiniMap::MiniMapSize = Size(320.0f, 224.0f);
const Vec2 MiniMap::MiniMapMargin = Vec2(32.0f, 48.0f);

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
	this->miniMapTerrainObjects = std::map<MiniMapTerrainObject*, float>();
	this->miniMapObjects = std::map<MiniMapObject*, float>();
	this->rootNode = Node::create();
	this->background = DrawNode::create();
	this->squallyMarker = nullptr;

	this->background->drawSolidRect(-Vec2(MiniMap::MiniMapSize) / 2.0f, Vec2(MiniMap::MiniMapSize) / 2.0f, Color4F(0, 0, 0, 0.5f));
	
	this->addLayerDeserializers({
			ObjectLayerDeserializer::create({
				{ MiniMapObjectDeserializer::MapKeyTypeObject, MiniMapObjectDeserializer::create() },
				{ MiniMapTerrainDeserializer::MapKeyTypeTerrain, MiniMapTerrainDeserializer::create() },
			})
		}
	);

	this->setVisible(false);

	this->mapNode->setScale(MiniMap::MiniMapScale);
	
	this->rootNode->addChild(this->background);
	this->rootNode->addChild(this->mapClip);
	this->rootNode->addChild(this->contentNode);
	this->addChild(this->rootNode);
}

MiniMap::~MiniMap()
{
}

void MiniMap::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();
}

void MiniMap::onHackerModeEnable()
{
	super::onHackerModeEnable();

	this->rootNode->setVisible(false);
}

void MiniMap::onHackerModeDisable()
{
	super::onHackerModeEnable();

	this->rootNode->setVisible(true);
}

void MiniMap::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	const Vec2 Offset = Vec2(visibleSize - MiniMapSize) / 2.0f - MiniMapMargin;

	this->rootNode->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f) + Offset);
}

void MiniMap::initializeListeners()
{
	super::initializeListeners();
}

void MiniMap::update(float dt)
{
	super::update(dt);

	this->positionMiniMap();
	this->positionEntityIcons();
}

bool MiniMap::loadMap(std::string mapResource)
{
	if (this->map != nullptr)
	{
		this->mapNode->removeChild(this->map);
		this->squallyMarker = nullptr;
	}

	this->setVisible(true);

	this->miniMapTerrainObjects.clear();
	this->miniMapObjects.clear();
	
	this->mapResource = mapResource;
	this->map = GameMap::deserialize(this->mapResource, this->layerDeserializers, true, true);
	
	if (this->map != nullptr)
	{
		this->squallyMarker = DrawNode::create();

		static const Size SquallySize = Size(128.0f, 128.0f);

		this->squallyMarker->drawSolidRect(-Vec2(SquallySize / 2.0f), Vec2(SquallySize / 2.0f), Color4F::MAGENTA);

		this->mapNode->addChild(this->map);
		this->mapNode->addChild(this->squallyMarker);

		this->initializeObjectLists();

		return true;
	}

	return false;
}

void MiniMap::initializeObjectLists()
{
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
		this->squallyMap = GameUtils::getFirstParentOfType<GameMap>(this->squally);
	}, Squally::MapKey);
	
	ObjectEvents::QueryObjects(QueryObjectsArgs<MiniMapTerrainObject>([=](MiniMapTerrainObject* terrainObject)
	{
		// All layers are forced to a depth of 0.0f, but we cache the original depth
		this->miniMapTerrainObjects[terrainObject] = GameUtils::getDepthUntil<GameMap>(terrainObject);

		terrainObject->setPositionZ(0.0f);
		terrainObject->detachAllBehavior();

	}), MiniMapTerrainObject::TagMiniMapTerrain);
	
	ObjectEvents::QueryObjects(QueryObjectsArgs<MiniMapObject>([=](MiniMapObject* miniMapObject)
	{
		// All layers are forced to a depth of 0.0f, but we cache the original depth
		this->miniMapObjects[miniMapObject] = GameUtils::getDepthUntil<GameMap>(miniMapObject);

		miniMapObject->setPositionZ(0.0f);

	}), MiniMapObject::TagMiniMapObject);

	if (this->map != nullptr)
	{
		for (auto next : this->map->getMapLayers())
		{
			next->setPositionZ(0.0f);
		}
	}
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

void MiniMap::positionEntityIcons()
{
	if (this->squally == nullptr || this->squallyMarker == nullptr)
	{
		return;
	}

	Vec2 squallyLocation = GameUtils::getWorldCoords(this->squally);

	this->squallyMarker->setPosition(squallyLocation);
}

void MiniMap::positionMiniMap()
{
	this->mapNode->setPosition(-GameCamera::getInstance()->getCameraPosition() * MiniMap::MiniMapScale);

	float squallyDepth = GameUtils::getDepthUntil<GameMap>(this->squally);

	for (auto next : this->miniMapTerrainObjects)
	{
		MiniMapTerrainObject* terrain = next.first;
		float depth = next.second;

		terrain->setVisible(std::abs(depth - squallyDepth) <= CollisionObject::CollisionZThreshold);
	}

	for (auto next : this->miniMapObjects)
	{
		MiniMapObject* object = next.first;
		float depth = next.second;

		object->setVisible(std::abs(depth - squallyDepth) <= CollisionObject::CollisionZThreshold);
	}
}
