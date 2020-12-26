#include "GameMap.h"

#include "cocos/2d/CCFastTMXLayer.h"
#include "cocos/2d/CCFastTMXTiledMap.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/platform/CCFileUtils.h"

#include "Engine/Deserializers/LayerDeserializer.h"
#include "Engine/Events/HackableEvents.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Maps/ObjectifiedTile.h"
#include "Engine/Maps/MapLayer.h"
#include "Engine/Maps/TileLayer.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/EngineCollisionTypes.h"
#include "Engine/UI/UIBoundObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"

#include "Resources/MapResources.h"

const std::string GameMap::KeyTypeCollision = "collision";

using namespace cocos2d;

cocos_experimental::TMXTiledMap* GameMap::parse(std::string mapFileName)
{
	cocos_experimental::TMXTiledMap* mapRaw = cocos_experimental::TMXTiledMap::create(mapFileName);

	return mapRaw;
}

GameMap* GameMap::deserialize(std::string mapFileName, cocos_experimental::TMXTiledMap* mapRaw, std::vector<LayerDeserializer*> layerDeserializers, bool disableEvents, bool disableBounds)
{
	if (mapRaw == nullptr)
	{
		return nullptr;
	}

	std::map<int, MapLayer*> deserializedLayerMap = std::map<int, MapLayer*>();
	std::vector<cocos_experimental::TMXLayer*> tileLayers = std::vector<cocos_experimental::TMXLayer*>();
	std::vector<MapLayer*> deserializedLayers = std::vector<MapLayer*>();

	// Callback to receive deserialized layers as they are parsed by their deserializers
	auto onDeserializeCallback = [&](LayerDeserializer::LayerDeserializationArgs args)
	{
		deserializedLayerMap[args.layerIndex] = args.mapLayer;
	};

	Size mapSize = Size(mapRaw->getMapSize().width * mapRaw->getTileSize().width, mapRaw->getMapSize().height * mapRaw->getTileSize().height);
	bool isIsometric = mapRaw->getMapOrientation() == MapOrientation::Isometric;

	if (isIsometric)
	{
		mapSize.width /= 2.0f;
	}
	
	for (auto next : mapRaw->getObjectGroups())
	{
		ValueMap properties = next->getProperties();

		properties[GameObject::MapKeyName] = next->getGroupName();
		properties[GameObject::MapKeyId] = next->layerIndex;

		std::string layerType = GameUtils::getKeyOrDefault(properties, MapLayer::MapKeyType, Value("")).asString();

		LayerDeserializer::LayerDeserializationRequestArgs args = LayerDeserializer::LayerDeserializationRequestArgs(
			properties,
			next->getObjects(),
			next->layerIndex,
			mapFileName,
			mapSize,
			isIsometric,
			onDeserializeCallback
		);

		for (auto deserializer : layerDeserializers)
		{
			if (deserializer->getLayerType() == layerType)
			{
				deserializer->deserialize(&args);
			}

			if (args.isHandled())
			{
				break;
			}
		}
	}

	// Pull out tile layers
	for (auto next : mapRaw->getChildren())
	{
		cocos_experimental::TMXLayer* tileLayer = dynamic_cast<cocos_experimental::TMXLayer*>(next);

		if (tileLayer != nullptr)
		{
			tileLayers.push_back(tileLayer);
		}
	}

	// Deserialize tiles (separate step from pulling them out because deserialization removes the child and would ruin the getChildren() iterator)
	for (auto next : tileLayers)
	{
		deserializedLayerMap[next->layerIndex] = TileLayer::deserialize(next);
	}

	// Convert from map to ordered vector
	for (auto next : deserializedLayerMap)
	{
		deserializedLayers.push_back(next.second);
	}
	
	if (!disableBounds && !isIsometric)
	{
		MapLayer* edgeCollisionLayer = MapLayer::create({ }, "edge_collision");

		const float EdgeThickness = 256.0f;

		CollisionObject* topCollision = CollisionObject::create(CollisionObject::createBox(Size(mapSize.width + EdgeThickness * 2.0f, EdgeThickness)), (CollisionType)EngineCollisionTypes::Solid, CollisionObject::Properties(false, false));
		CollisionObject* bottomCollision = CollisionObject::create(CollisionObject::createBox(Size(mapSize.width + EdgeThickness * 2.0f, EdgeThickness)), (CollisionType)EngineCollisionTypes::Solid, CollisionObject::Properties(false, false));
		CollisionObject* leftCollision = CollisionObject::create(CollisionObject::createBox(Size(EdgeThickness, mapSize.height)), (CollisionType)EngineCollisionTypes::Solid, CollisionObject::Properties(false, false));
		CollisionObject* rightCollision = CollisionObject::create(CollisionObject::createBox(Size(EdgeThickness, mapSize.height)), (CollisionType)EngineCollisionTypes::Solid, CollisionObject::Properties(false, false));

		edgeCollisionLayer->addChild(topCollision);
		edgeCollisionLayer->addChild(leftCollision);
		edgeCollisionLayer->addChild(rightCollision);
		edgeCollisionLayer->addChild(bottomCollision);

		topCollision->setCollisionDepth(2048.0f);
		leftCollision->setCollisionDepth(2048.0f);
		rightCollision->setCollisionDepth(2048.0f);
		bottomCollision->setCollisionDepth(2048.0f);

		topCollision->setName("Top collision");
		leftCollision->setName("Left collision");
		rightCollision->setName("Right collision");
		bottomCollision->setName("Bottom collision");

		topCollision->setPosition(Vec2(mapSize.width / 2.0f, mapSize.height + EdgeThickness / 2.0f));
		bottomCollision->setPosition(Vec2(mapSize.width / 2.0f, -EdgeThickness / 2.0f));
		leftCollision->setPosition(Vec2(-EdgeThickness / 2.0f, mapSize.height / 2.0f));
		rightCollision->setPosition(Vec2(mapSize.width + EdgeThickness / 2.0f, mapSize.height / 2.0f));

		deserializedLayers.push_back(edgeCollisionLayer);
	}

	// Create a special hud_target layer for top-level display items
	deserializedLayers.push_back(MapLayer::create({ { MapLayer::PropertyIsHackable, Value(true) }}, "hud_target"));

	GameMap* instance = new GameMap(mapFileName, deserializedLayers, mapRaw->getMapSize(), mapRaw->getTileSize(), (MapOrientation)mapRaw->getMapOrientation(), disableEvents, disableBounds);

	instance->autorelease();

	return instance;
}

GameMap::GameMap(std::string mapFileName, const std::vector<MapLayer*>& mapLayers, Size unitSize, Size tileSize, MapOrientation orientation, bool disableEvents, bool disableBounds)
{
	this->collisionLayers = std::vector<TileLayer*>();
	this->mapLayers = mapLayers;
	this->tileLayers = std::vector<TileLayer*>();
	this->layersToSort = std::vector<TileLayer*>();
	this->levelMapFileName = mapFileName;
	this->mapUnitSize = unitSize;
	this->mapTileSize = tileSize;
	this->orientation = orientation;
	this->disableEvents = disableEvents;
	this->disableBounds = disableBounds;

	for (auto next : this->mapLayers)
	{
		this->addChild(next);
	}

	if (this->orientation == MapOrientation::Isometric)
	{
		this->isometricMapPreparation();
	}
}

GameMap::~GameMap()
{
}

void GameMap::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void GameMap::initializeListeners()
{
	super::initializeListeners();

	if (disableEvents)
	{
		return;
	}
	
	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::EventHackerModeEnable, [=](EventCustom* eventCustom)
	{
		this->hackerModeEnable();
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::EventHackerModeDisable, [=](EventCustom* eventCustom)
	{
		this->hackerModeDisable();
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::EventHackableObjectOpen, [=](EventCustom* eventCustom)
	{
		this->hackerModeLayerFade();
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::EventHackableObjectClose, [=](EventCustom* eventCustom)
	{
		this->hackerModeLayerUnfade();
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(ObjectEvents::EventSpawnObjectDelegator, [=](EventCustom* eventCustom)
	{
		RequestObjectSpawnDelegatorArgs* args = static_cast<RequestObjectSpawnDelegatorArgs*>(eventCustom->getData());

		if (args != nullptr)
		{
			this->spawnObject(args);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(ObjectEvents::EventBindObjectToUI, [=](EventCustom* eventCustom)
	{
		RelocateObjectArgs* args = static_cast<RelocateObjectArgs*>(eventCustom->getData());

		if (args != nullptr)
		{
			this->moveObjectToTopLayer(args);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(ObjectEvents::EventElevateObject, [=](EventCustom* eventCustom)
	{
		RelocateObjectArgs* args = static_cast<RelocateObjectArgs*>(eventCustom->getData());

		if (args != nullptr)
		{
			this->moveObjectToElevateLayer(args);
		}
	}));
}

void GameMap::update(float dt)
{
	super::update(dt);

	this->isometricZSort();
}

std::string GameMap::getMapFileName()
{
	return this->levelMapFileName;
}

void GameMap::spawnObject(RequestObjectSpawnDelegatorArgs* args)
{
	if (args == nullptr)
	{
		return;
	}

	RequestObjectSpawnArgs* innerArgs = args->innerArgs;

	if (this->mapLayers.empty() || innerArgs->objectToSpawn == nullptr)
	{
		return;
	}

	bool isReentry = (innerArgs->objectToSpawn->getParent() != nullptr);
	bool retainPosition = (innerArgs->positionMode != PositionMode::Discard);

	if (innerArgs->positionMode == PositionMode::SetToOwner)
	{
		innerArgs->objectToSpawn->setPosition3D(GameUtils::getWorldCoords3D(innerArgs->spawner));
	}

	switch (innerArgs->spawnMethod)
	{
		case SpawnMethod::LayerBelow:
		{
			std::vector<MapLayer*>::iterator prevIt = this->mapLayers.end();

			for (auto it = this->mapLayers.begin(); it != this->mapLayers.end(); it++)
			{
				if (*it == args->sourceLayer)
				{
					if (prevIt != this->mapLayers.end())
					{
						GameUtils::changeParent(innerArgs->objectToSpawn, (*prevIt), retainPosition);
						innerArgs->handled = true;

						return;
					}
					else
					{
						GameUtils::changeParent(innerArgs->objectToSpawn, (*it), retainPosition);
						innerArgs->handled = true;

						return;
					}
				}

				prevIt = it;
			}

			break;
		}
		case SpawnMethod::TopMost:
		{
			if (!this->mapLayers.empty())
			{
				GameUtils::changeParent(innerArgs->objectToSpawn, this->mapLayers.back(), retainPosition);
				innerArgs->handled = true;
				return;
			}
			
			break;
		}
		case SpawnMethod::Below:
		{
			for (auto layer : this->mapLayers)
			{
				if (layer == args->sourceLayer)
				{
					GameUtils::changeParent(innerArgs->objectToSpawn, layer, retainPosition, 0);
					innerArgs->handled = true;

					return;
				}
			}
		}
		default:
		case SpawnMethod::Above:
		{
			for (auto layer : this->mapLayers)
			{
				if (layer == args->sourceLayer)
				{
					GameUtils::changeParent(innerArgs->objectToSpawn, layer, retainPosition);
					innerArgs->handled = true;
					
					return;
				}
			}
			
			break;
		}
	}
}

void GameMap::moveObjectToTopLayer(RelocateObjectArgs* args)
{
	if (this->mapLayers.empty())
	{
		return;
	}
	
	this->mapLayers.back()->addChild(UIBoundObject::create(args->relocatedObject));
}

void GameMap::moveObjectToElevateLayer(RelocateObjectArgs* args)
{
	if (this->mapLayers.empty())
	{
		return;
	}

	for (auto layer : this->mapLayers)
	{
		if (layer->isElevateTarget())
		{
			GameUtils::changeParent(args->relocatedObject, layer, true);
		}
	}
}

void GameMap::hackerModeEnable()
{
	for (auto layer : this->mapLayers)
	{
		if (!layer->isHackable())
		{
			layer->setVisible(false);
		}
	}
}

void GameMap::hackerModeDisable()
{
	for (auto layer : this->mapLayers)
	{
		layer->setVisible(true);
	}
}

void GameMap::hackerModeLayerFade()
{
	for (auto layer : this->mapLayers)
	{
		if (layer->isHackable())
		{
			layer->setOpacity(128);
		}
	}
}

void GameMap::hackerModeLayerUnfade()
{
	for (auto layer : this->mapLayers)
	{
		layer->setOpacity(255);
	}
}

Size GameMap::getMapSize()
{
	Size unitSize = this->getMapUnitSize();
	Size tileSize = this->getMapTileSize();

	return Size(unitSize.width * tileSize.width, unitSize.height * tileSize.height);
}

Size GameMap::getMapUnitSize()
{
	return this->mapUnitSize;
}

Size GameMap::getMapTileSize()
{
	return this->mapTileSize;
}

bool GameMap::isIsometric()
{
	return this->orientation == MapOrientation::Isometric;
}
bool GameMap::isPlatformer()
{
	return this->orientation == MapOrientation::Platformer;
}

void GameMap::appendLayer(MapLayer* mapLayer)
{
	this->mapLayers.push_back(mapLayer);

	this->addChild(mapLayer);
}

void GameMap::setCollisionLayersVisible(bool isVisible)
{
	for (auto layer : this->collisionLayers)
	{
		layer->setVisible(isVisible);
	}
}

std::vector<TileLayer*> GameMap::getCollisionLayers()
{
	return this->collisionLayers;
}

std::vector<MapLayer*> GameMap::getMapLayers()
{
	return this->mapLayers;
}

void GameMap::isometricZSort()
{
	if (this->orientation != MapOrientation::Isometric)
	{
		return;
	}

	for (auto layer : this->layersToSort)
	{
		for (auto child : layer->getChildren())
		{
			GameObject* object = dynamic_cast<GameObject*>(child);

			// Only z sort the objects in the map marked for z sorting (top left lowest, bottom right highest)
			if (object != nullptr && object->isZSorted())
			{
				// Note: This sets local Z order, so make sure objects are on the same layer if you want them to dynamically sort.
				Vec2 position = object->getParent()->convertToWorldSpace(object->getPosition());

				if (dynamic_cast<ObjectifiedTile*>(object) != nullptr)
				{
					position.y += this->mapTileSize.height / 2.0f;
				}

				object->setLocalZOrder((int)(-position.y));
			}
		}
	}
}

void GameMap::isometricMapPreparation()
{
	if (this->orientation != MapOrientation::Isometric)
	{
		return;
	}
	
	for (auto it = this->getChildren().begin(); it != this->getChildren().end(); it++)
	{
		// Tile layers:
		if (dynamic_cast<TileLayer*>(*it) != nullptr)
		{
			TileLayer* tileLayer = dynamic_cast<TileLayer*>(*it);

			if (tileLayer->getType() == GameMap::KeyTypeCollision)
			{
				// Collision layer
				this->collisionLayers.push_back(tileLayer);
			}
			else
			{
				// Standard tile layer
				this->tileLayers.push_back(tileLayer);
			}
		}
		// Object layers
		else if (dynamic_cast<MapLayer*>(*it) != nullptr)
		{
			MapLayer* objectLayer = dynamic_cast<MapLayer*>(*it);

			if (objectLayer->getLayerType() == "objects")
			{
				// Iterate through remaining layers to find the next tile layer
				for (auto itClone = std::vector<Node*>::iterator(it); itClone != this->getChildren().end(); itClone++)
				{
					TileLayer* nextTileLayer = dynamic_cast<TileLayer*>(*itClone);

					// Pull out objects and inject them into the next highest tile layer (allows for proper dynamic Z sorting)
					if (nextTileLayer != nullptr && nextTileLayer->isObjectified() && nextTileLayer->getType() != GameMap::KeyTypeCollision)
					{
						cocos2d::Vector<Node*> children = objectLayer->getChildren();

						for (auto childIt = children.begin(); childIt != children.end(); childIt++)
						{
							GameUtils::changeParent(*childIt, nextTileLayer, true);
						}

						this->layersToSort.push_back(nextTileLayer);
					}
				}
			}
		}

		this->setCollisionLayersVisible(false);
	}
}
