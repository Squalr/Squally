#include "MapLayer.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Maps/GameObject.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

const std::string MapLayer::KeyType = "type";
const std::string MapLayer::MapKeyPropertyName = "name";
const std::string MapLayer::MapKeyPropertyValue = "value";
const std::string MapLayer::MapKeyPropertyDepth = "depth";
const std::string MapLayer::MapKeyPropertyIsHackable = "is-hackable";
const std::string MapLayer::MapKeyPropertyIsElevateTarget = "is-elevate-target";

MapLayer* MapLayer::create(const ValueMap& initProperties, std::string name, const std::vector<GameObject*>& objects)
{
	MapLayer* instance = new MapLayer(initProperties, name, objects);

	instance->autorelease();

	return instance;
}

MapLayer::MapLayer() 
{
}

MapLayer::MapLayer(const ValueMap& initProperties, std::string name) : MapLayer(initProperties, name, std::vector<GameObject*>())
{
}

MapLayer::MapLayer(const ValueMap& initProperties, std::string name, const std::vector<GameObject*>& objects)
{
	this->layerName = name;
	this->properties = initProperties;

	this->setPositionZ(GameUtils::getKeyOrDefault(this->properties, MapLayer::MapKeyPropertyDepth, Value(0.0f)).asFloat());

	for (auto it = objects.begin(); it != objects.end(); it++)
	{
		this->addChild(*it);
	}
}

MapLayer::~MapLayer()
{
}

void MapLayer::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(ObjectEvents::EventSpawnObject, [=](EventCustom* eventArgs)
	{
		ObjectEvents::RequestObjectSpawnArgs* args = (ObjectEvents::RequestObjectSpawnArgs*)eventArgs->getUserData();

		if (GameUtils::getFirstParentOfType<MapLayer>(args->spawner) == this)
		{
			// Delegate the spawning to the map, which will decide where to place the object
			ObjectEvents::TriggerObjectSpawnDelegator(ObjectEvents::RequestObjectSpawnDelegatorArgs(this, args->spawner, args->objectToSpawn, args->spawnMethod, args->positionMode));
		}
	}));
}

bool MapLayer::isHackable()
{
	return GameUtils::getKeyOrDefault(this->properties, MapLayer::MapKeyPropertyIsHackable, Value(false)).asBool();
}

bool MapLayer::isElevateTarget()
{
	return GameUtils::getKeyOrDefault(this->properties, MapLayer::MapKeyPropertyIsElevateTarget, Value(false)).asBool();
}
