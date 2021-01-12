#include "MiniMap.h"

#include "cocos/2d/CCDrawNode.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Deserializers/Platformer/MiniMapCollisionDeserializer.h"
#include "Deserializers/Platformer/MiniMapObjectDeserializer.h"
#include "Deserializers/Platformer/MiniMapTerrainDeserializer.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Deserializers/LayerDeserializer.h"
#include "Engine/Deserializers/Objects/ObjectLayerDeserializer.h"
#include "Engine/Events/InventoryEvents.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Terrain/MiniMapTerrainObject.h"
#include "Engine/UI/SmartClippingNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"
#include "Engine/Maps/MiniGameMap.h"
#include "Engine/Maps/MapLayer.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/MiniMap/MiniMapObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

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
	this->rootNode = Node::create();
	this->mapNode = Node::create();
	this->contentNode = Node::create();
	this->mapClip = SmartClippingNode::create(this->mapNode, MiniMap::MiniMapSize);
	this->map = nullptr;
	this->mapResource = "";
	this->squally = nullptr;
	this->miniMapTerrainObjects = std::map<MiniMapTerrainObject*, float>();
	this->miniMapObjects = std::map<MiniMapObject*, float>();
	this->background = DrawNode::create();
	this->squallyMarker = nullptr;
	this->squallyInventory = nullptr;
	this->requiredItemKey = SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyLevelMiniMapRequiredItem, Value("")).asString();
	this->isShown = false;

	this->background->drawSolidRect(-Vec2(MiniMap::MiniMapSize) / 2.0f, Vec2(MiniMap::MiniMapSize) / 2.0f, Color4F(0, 0, 0, 0.5f));
	
	this->addLayerDeserializers({
			ObjectLayerDeserializer::create({
				{ MiniMapObjectDeserializer::MapKeyTypeObject, MiniMapObjectDeserializer::create() },
				{ MiniMapCollisionDeserializer::MapKeyTypeCollision, MiniMapCollisionDeserializer::create() },
				{ MiniMapTerrainDeserializer::MapKeyTypeTerrain, MiniMapTerrainDeserializer::create() },
			})
		}
	);

	this->rootNode->setOpacity(0);

	this->mapNode->setScale(MiniMap::MiniMapScale);
	
	this->rootNode->addChild(this->background);
	this->rootNode->addChild(this->mapClip);
	this->rootNode->addChild(this->contentNode);
	this->addChild(this->rootNode);
}

MiniMap::~MiniMap()
{
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

	this->setPositioning();
}

void MiniMap::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventShowMiniMap, [=](EventCustom* eventCustom)
	{
		this->show();
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventHideMiniMap, [=](EventCustom* eventCustom)
	{
		this->hide();
	}));
}

void MiniMap::update(float dt)
{
	super::update(dt);

	this->positionMiniMap();
	this->positionEntityIcons();
}

void MiniMap::show(bool instant)
{
	if (this->isShown)
	{
		return;
	}

	this->isShown = true;
	this->rootNode->stopAllActions();
	
	if (instant)
	{
		this->rootNode->setOpacity(255);
	}
	else
	{
		this->rootNode->runAction(FadeTo::create(0.25f, 255));
	}
}

void MiniMap::hide(bool instant)
{
	if (!this->isShown)
	{
		return;
	}
	
	this->isShown = false;
	this->rootNode->stopAllActions();

	if (instant)
	{
		this->rootNode->setOpacity(0);
	}
	else
	{
		this->rootNode->runAction(FadeTo::create(0.25f, 0));
	}
}

void MiniMap::setPositioning(std::string miniMapPositioning)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	const Vec2 DefaultPosition = (Vec2(visibleSize) - Vec2(MiniMapSize)) / 2.0f - MiniMapMargin;
	Vec2 newPosition = Vec2::ZERO;
	
	if (miniMapPositioning == "top-left")
	{
		newPosition = Vec2(-DefaultPosition.x, DefaultPosition.y);
	}
	else if (miniMapPositioning == "bottom-left")
	{
		newPosition = Vec2(-DefaultPosition.x, -DefaultPosition.y);
	}
	else if (miniMapPositioning== "bottom-right")
	{
		newPosition = Vec2(DefaultPosition.x, -DefaultPosition.y);
	}
	else
	{
		newPosition = Vec2(DefaultPosition.x, DefaultPosition.y);
	}

	this->rootNode->setPosition(Vec2(visibleSize) / 2.0f + newPosition);
}

bool MiniMap::loadMapFromTmx(std::string mapResource, cocos_experimental::TMXTiledMap* mapRaw)
{
	if (this->map != nullptr)
	{
		this->mapNode->removeChild(this->map);
		this->squallyMarker = nullptr;
	}

	this->miniMapTerrainObjects.clear();
	this->miniMapObjects.clear();
	
	this->mapResource = mapResource;
	this->map = MiniGameMap::deserialize(this->mapResource, mapRaw, this->layerDeserializers);
	
	if (this->map != nullptr)
	{
		this->squallyMarker = DrawNode::create();

		static const Size SquallySize = Size(128.0f, 128.0f);

		this->squallyMarker->drawSolidRect(-Vec2(SquallySize / 2.0f), Vec2(SquallySize / 2.0f), Color4F::MAGENTA);

		this->mapNode->addChild(this->map);
		this->mapNode->addChild(this->squallyMarker);

		this->initializeMapData();

		return true;
	}

	return false;
}

void MiniMap::initializeMapData()
{
	bool hideMiniMap = SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyLevelHideMiniMap, Value(false)).asBool();

	if (!this->requiredItemKey.empty() && !hideMiniMap)
	{
		this->show();
	}

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
		this->squallyMap = GameUtils::GetFirstParentOfType<MiniGameMap>(this->squally);
		
		this->squally->watchForAttachedBehavior<EntityInventoryBehavior>([=](EntityInventoryBehavior* entityInventoryBehavior)
		{
			this->squallyInventory = entityInventoryBehavior->getInventory();

			this->addEventListenerIgnorePause(EventListenerCustom::create(InventoryEvents::EventInventoryInstanceChangedPrefix + this->squallyInventory->getSaveKey(), [=](EventCustom* eventCustom)
			{
				if (this->hasRequiredItem())
				{
					this->show();
				}
			}));

			if (this->hasRequiredItem())
			{
				this->show();
			}
		});
	}, Squally::MapKey);

	GameUtils::getChildrenOfType<MiniMapTerrainObject>(this->map, [=](MiniMapTerrainObject* terrainObject)
	{
		// All layers are forced to a depth of 0.0f, but we cache the original depth
		this->miniMapTerrainObjects[terrainObject] = GameUtils::getDepthUntil<MiniGameMap>(terrainObject);

		terrainObject->setPositionZ(0.0f);
		terrainObject->detachAllBehavior();
	});

	GameUtils::getChildrenOfType<MiniMapObject>(this->map, [=](MiniMapObject* miniMapObject)
	{
		// All layers are forced to a depth of 0.0f, but we cache the original depth
		this->miniMapObjects[miniMapObject] = GameUtils::getDepthUntil<MiniGameMap>(miniMapObject);

		miniMapObject->setPositionZ(0.0f);
		miniMapObject->detachAllBehavior();
	});

	if (this->map != nullptr)
	{
		for (auto next : this->map->getMapLayers())
		{
			next->setPositionZ(0.0f);
		}
	}
}

bool MiniMap::hasRequiredItem()
{
	bool hideMiniMap = SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyLevelHideMiniMap, Value(false)).asBool();

	if (hideMiniMap || this->squallyInventory == nullptr)
	{
		return false;
	}

	if (this->requiredItemKey.empty() || this->squallyInventory->hasItemOfName(this->requiredItemKey))
	{
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

	float squallyDepth = GameUtils::getDepthUntil<MiniGameMap>(this->squally);
	
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

		object->depthVisibilityNode->setVisible(std::abs(depth - squallyDepth) <= CollisionObject::CollisionZThreshold);
	}
}
