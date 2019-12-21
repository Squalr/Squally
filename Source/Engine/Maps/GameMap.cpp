#include "GameMap.h"

#include "cocos/2d/CCFastTMXLayer.h"
#include "cocos/2d/CCFastTMXTiledMap.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/physics/CCPhysicsBody.h"
#include "cocos/platform/CCFileUtils.h"

#include "Engine/Deserializers/LayerDeserializer.h"
#include "Engine/Events/HackableEvents.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Maps/ObjectifiedTile.h"
#include "Engine/Maps/MapLayer.h"
#include "Engine/Maps/TileLayer.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/EngineCollisionTypes.h"
#include "Engine/SmartNode.h"
#include "Engine/UI/UIBoundObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"

#include "Resources/MapResources.h"

const std::string GameMap::KeyTypeCollision = "collision";

using namespace cocos2d;

GameMap::GameMap(std::string mapFileName, const std::vector<MapLayer*>& mapLayers, Size unitSize, Size tileSize, MapOrientation orientation)
{
	this->collisionLayers = std::vector<TileLayer*>();
	this->mapLayers = mapLayers;
	this->tileLayers = std::vector<TileLayer*>();
	this->layersToSort = std::vector<TileLayer*>();
	this->levelMapFileName = mapFileName;
	this->mapUnitSize = unitSize;
	this->mapTileSize = tileSize;
	this->orientation = orientation;

	for (auto it = this->mapLayers.begin(); it != this->mapLayers.end(); it++)
	{
		this->addChild(*it);
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
		ObjectEvents::RequestObjectSpawnDelegatorArgs* args = static_cast<ObjectEvents::RequestObjectSpawnDelegatorArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			this->spawnObject(args);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(ObjectEvents::EventBindObjectToUI, [=](EventCustom* eventCustom)
	{
		ObjectEvents::RelocateObjectArgs* args = static_cast<ObjectEvents::RelocateObjectArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			this->moveObjectToTopLayer(args);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(ObjectEvents::EventElevateObject, [=](EventCustom* eventCustom)
	{
		ObjectEvents::RelocateObjectArgs* args = static_cast<ObjectEvents::RelocateObjectArgs*>(eventCustom->getUserData());

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

GameMap* GameMap::deserialize(std::string mapFileName, std::vector<LayerDeserializer*> layerDeserializers)
{
	cocos_experimental::TMXTiledMap* mapRaw = cocos_experimental::TMXTiledMap::create(mapFileName);

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
	else
	{
		MapLayer* edgeCollisionLayer = MapLayer::create({ }, "edge_collision");

		const float EdgeThickness = 256.0f;

		CollisionObject* topCollision = CollisionObject::create(PhysicsBody::createBox(Size(mapSize.width + EdgeThickness * 2.0f, EdgeThickness)), (CollisionType)EngineCollisionTypes::Solid, false, false);
		CollisionObject* bottomCollision = CollisionObject::create(PhysicsBody::createBox(Size(mapSize.width + EdgeThickness * 2.0f, EdgeThickness)), (CollisionType)EngineCollisionTypes::KillPlane, false, false);
		CollisionObject* leftCollision = CollisionObject::create(PhysicsBody::createBox(Size(EdgeThickness, mapSize.height)), (CollisionType)EngineCollisionTypes::Solid, false, false);
		CollisionObject* rightCollision = CollisionObject::create(PhysicsBody::createBox(Size(EdgeThickness, mapSize.height)), (CollisionType)EngineCollisionTypes::Solid, false, false);

		edgeCollisionLayer->addChild(topCollision);
		edgeCollisionLayer->addChild(leftCollision);
		edgeCollisionLayer->addChild(rightCollision);
		edgeCollisionLayer->addChild(bottomCollision);

		topCollision->setPosition(Vec2(mapSize.width / 2.0f, mapSize.height + EdgeThickness / 2.0f));
		bottomCollision->setPosition(Vec2(mapSize.width / 2.0f, -EdgeThickness / 2.0f));
		leftCollision->setPosition(Vec2(-EdgeThickness / 2.0f, mapSize.height / 2.0f));
		rightCollision->setPosition(Vec2(mapSize.width + EdgeThickness / 2.0f, mapSize.height / 2.0f));

		deserializedLayers.push_back(edgeCollisionLayer);
	}

	// Fire event requesting the deserialization of this layer -- the appropriate deserializer class should handle it
	for (auto it = mapRaw->getObjectGroups().begin(); it != mapRaw->getObjectGroups().end(); it++)
	{
		std::string layerType = GameUtils::getKeyOrDefault((*it)->getProperties(), MapLayer::MapKeyType, Value("")).asString();

		LayerDeserializer::LayerDeserializationRequestArgs args = LayerDeserializer::LayerDeserializationRequestArgs(
			(*it)->getProperties(),
			(*it)->getObjects(),
			(*it)->layerIndex,
			mapFileName,
			mapSize,
			isIsometric,
			onDeserializeCallback
		);

		for (auto deserializerIt = layerDeserializers.begin(); deserializerIt != layerDeserializers.end(); deserializerIt++)
		{
			if ((*deserializerIt)->getLayerType() == layerType)
			{
				(*deserializerIt)->deserialize(&args);
			}

			if (args.isHandled())
			{
				break;
			}
		}
	}

	// Pull out tile layers
	for (auto it = mapRaw->getChildren().begin(); it != mapRaw->getChildren().end(); it++)
	{
		cocos_experimental::TMXLayer* tileLayer = dynamic_cast<cocos_experimental::TMXLayer*>(*it);

		if (tileLayer != nullptr)
		{
			tileLayers.push_back(tileLayer);
		}
	}

	// Deserialize tiles (separate step from pulling them out because deserialization removes the child and would ruin the getChildren() iterator)
	for (auto it = tileLayers.begin(); it != tileLayers.end(); it++)
	{
		deserializedLayerMap[(*it)->layerIndex] = TileLayer::deserialize((*it));
	}

	// Convert from map to ordered vector
	for (auto it = deserializedLayerMap.begin(); it != deserializedLayerMap.end(); it++)
	{
		deserializedLayers.push_back(it->second);
	}

	// Create a special hud_target layer for top-level display items
	deserializedLayers.push_back(MapLayer::create({ { MapLayer::MapKeyPropertyIsHackable, Value(true) }}, "hud_target"));

	GameMap* instance = new GameMap(mapFileName, deserializedLayers, mapRaw->getMapSize(), mapRaw->getTileSize(), (MapOrientation)mapRaw->getMapOrientation());

	instance->autorelease();

	return instance;
}

std::string GameMap::getMapFileName()
{
	return this->levelMapFileName;
}

void GameMap::spawnObject(ObjectEvents::RequestObjectSpawnDelegatorArgs* args)
{
	if (this->mapLayers.empty() || args->objectToSpawn == nullptr)
	{
		return;
	}

	bool isReentry = (args->objectToSpawn->getParent() != nullptr);
	bool retainPosition = (args->positionMode != ObjectEvents::PositionMode::Discard);

	if (args->positionMode == ObjectEvents::PositionMode::SetToOwner)
	{
		args->objectToSpawn->setPosition3D(GameUtils::getWorldCoords3D(args->spawner));
	}

	switch (args->spawnMethod)
	{
		case ObjectEvents::SpawnMethod::Below:
		{
			std::vector<MapLayer*>::iterator prevIt = this->mapLayers.end();

			for (auto it = this->mapLayers.begin(); it != this->mapLayers.end(); it++)
			{
				if (*it == args->sourceLayer)
				{
					if (prevIt != this->mapLayers.end())
					{
						GameUtils::changeParent(args->objectToSpawn, (*prevIt), retainPosition, isReentry);
					}
					else
					{
						GameUtils::changeParent(args->objectToSpawn, (*it), retainPosition, isReentry);
					}
				}

				prevIt = it;
			}

			break;
		}
		default:
		case ObjectEvents::SpawnMethod::Above:
		{
			for (auto it = this->mapLayers.begin(); it != this->mapLayers.end(); it++)
			{
				if (*it == args->sourceLayer)
				{
					GameUtils::changeParent(args->objectToSpawn, (*it), retainPosition, isReentry);
				}
			}
			
			break;
		}
	}
}

void GameMap::moveObjectToTopLayer(ObjectEvents::RelocateObjectArgs* args)
{
	if (this->mapLayers.empty())
	{
		return;
	}
	
	this->mapLayers.back()->addChild(UIBoundObject::create(args->relocatedObject));
}

void GameMap::moveObjectToElevateLayer(ObjectEvents::RelocateObjectArgs* args)
{
	if (this->mapLayers.empty())
	{
		return;
	}

	for (auto it = this->mapLayers.begin(); it != this->mapLayers.end(); it++)
	{
		if ((*it)->isElevateTarget())
		{
			GameUtils::changeParent(args->relocatedObject, *it, true);
		}
	}
}

void GameMap::hackerModeEnable()
{
	for (auto it = this->mapLayers.begin(); it != this->mapLayers.end(); it++)
	{
		if (!(*it)->isHackable())
		{
			(*it)->setVisible(false);
		}
	}
}

void GameMap::hackerModeDisable()
{
	for (auto it = this->mapLayers.begin(); it != this->mapLayers.end(); it++)
	{
		(*it)->setVisible(true);
	}
}

void GameMap::hackerModeLayerFade()
{
	for (auto it = this->mapLayers.begin(); it != this->mapLayers.end(); it++)
	{
		if ((*it)->isHackable())
		{
			(*it)->setOpacity(128);
		}
	}
}

void GameMap::hackerModeLayerUnfade()
{
	for (auto it = this->mapLayers.begin(); it != this->mapLayers.end(); it++)
	{
		(*it)->setOpacity(255);
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
	for (auto it = this->collisionLayers.begin(); it != this->collisionLayers.end(); it++)
	{
		(*it)->setVisible(isVisible);
	}
}

std::vector<TileLayer*> GameMap::getCollisionLayers()
{
	return this->collisionLayers;
}

void GameMap::isometricZSort()
{
	if (this->orientation != MapOrientation::Isometric)
	{
		return;
	}

	for (auto it = this->layersToSort.begin(); it != this->layersToSort.end(); it++)
	{
		for (auto childIt = (*it)->getChildren().begin(); childIt != (*it)->getChildren().end(); childIt++)
		{
			GameObject* object = dynamic_cast<GameObject*>(*childIt);

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
