#include "MapLayer.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Maps/GameObject.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

const std::string MapLayer::MapKeyType = "type";
const std::string MapLayer::PropertyName = "name";
const std::string MapLayer::PropertyValue = "value";
const std::string MapLayer::PropertyDepth = "depth";
const std::string MapLayer::PropertyIsHackable = "is-hackable";
const std::string MapLayer::PropertyIsElevateTarget = "is-elevate-target";
const std::string MapLayer::PropertyZSort = "z-sort";

MapLayer* MapLayer::create(const ValueMap& properties, std::string name, std::string type, const std::vector<GameObject*>& objects)
{
	MapLayer* instance = new MapLayer(properties, name, type, objects);

	instance->autorelease();

	return instance;
}

MapLayer::MapLayer() 
{
}

MapLayer::MapLayer(const ValueMap& properties, std::string name, std::string type) : MapLayer(properties, name, type, std::vector<GameObject*>())
{
}

MapLayer::MapLayer(const ValueMap& properties, std::string name, std::string type, const std::vector<GameObject*>& objects) : super(properties)
{
	this->layerName = name;
	this->layerType = type;
	this->uniqueIdentifier = this->layerName + "_" + this->layerType + "_" + GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyId, Value("")).asString();

	this->autoZSort = GameUtils::getKeyOrDefault(this->properties, MapLayer::PropertyZSort, Value(false)).asBool();

	this->setPositionZ(GameUtils::getKeyOrDefault(this->properties, MapLayer::PropertyDepth, Value(0.0f)).asFloat());
	
	// We need to re-add the ID tag, as in the GameObject parent class, ID will be empty and thus not tagged yet.
	this->addTag(this->uniqueIdentifier);

	for (auto object : objects)
	{
		this->addChild(object);
	}
}

MapLayer::~MapLayer()
{
}

void MapLayer::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(ObjectEvents::EventSpawnObject, [=](EventCustom* eventCustom)
	{
		RequestObjectSpawnArgs* args = static_cast<RequestObjectSpawnArgs*>(eventCustom->getData());

		if (GameUtils::getFirstParentOfType<MapLayer>(args->spawner) == this)
		{
			// Delegate the spawning to the map, which will decide where to place the object
			ObjectEvents::TriggerObjectSpawnDelegator(RequestObjectSpawnDelegatorArgs(this, args));
		}
	}));

	this->scheduleUpdate();
}

void MapLayer::update(float dt)
{
	super::update(dt);

	if (this->autoZSort)
	{
		for (auto child : this->getChildren())
		{
			child->setLocalZOrder(int32_t(child->getPositionZ()));	
		}
	}
}

bool MapLayer::isHackable()
{
	return GameUtils::getKeyOrDefault(this->properties, MapLayer::PropertyIsHackable, Value(false)).asBool();
}

bool MapLayer::isElevateTarget()
{
	return GameUtils::getKeyOrDefault(this->properties, MapLayer::PropertyIsElevateTarget, Value(false)).asBool();
}

std::string MapLayer::getLayerType()
{
	return this->layerType;
}
