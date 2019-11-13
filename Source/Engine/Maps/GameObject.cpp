#include "GameObject.h"

#include "cocos/base/CCValue.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/AttachedBehavior/AttachedBehavior.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"

using namespace cocos2d;

const std::string GameObject::MapKeyId = "id";
const std::string GameObject::MapKeyType = "type";
const std::string GameObject::MapKeyName = "name";
const std::string GameObject::MapKeyTag = "tag";
const std::string GameObject::MapKeyTags = "tags";
const std::string GameObject::MapKeyWidth = "width";
const std::string GameObject::MapKeyHeight = "height";
const std::string GameObject::MapKeyXPosition = "x";
const std::string GameObject::MapKeyYPosition = "y";
const std::string GameObject::MapKeyScale = "scale";
const std::string GameObject::MapKeyScaleX = "scale-x";
const std::string GameObject::MapKeyScaleY = "scale-y";
const std::string GameObject::MapKeyAutoScale = "auto-scale";
const std::string GameObject::MapKeyFlipX = "flip-x";
const std::string GameObject::MapKeyFlipY = "flip-y";
const std::string GameObject::MapKeyRepeatX = "repeat-x";
const std::string GameObject::MapKeyRepeatY = "repeat-y";
const std::string GameObject::MapKeyListenEvent = "listen-event";
const std::string GameObject::MapKeySendEvent = "send-event";
const std::string GameObject::MapKeyState = "state";
const std::string GameObject::MapKeyQuest = "quest";
const std::string GameObject::MapKeyQuestLine = "quest-line";
const std::string GameObject::MapKeyQuestTag = "quest-tag";
const std::string GameObject::MapKeyAttachedBehavior = "attached-behavior";
const std::string GameObject::MapKeyArgs = "args";
const std::string GameObject::MapKeyRotation = "rotation";
const std::string GameObject::MapKeyPoints = "points";
const std::string GameObject::MapKeyPolyLinePoints = "polylinePoints";

const std::string GameObject::MapKeyGid = "gid";

const std::string GameObject::MapKeyMetaIsIsometric = "meta_is_isometric";
const std::string GameObject::MapKeyMetaMapHeight = "meta_map_height";
const std::string GameObject::MapKeyMetaMapWidth = "meta_map_width";
const std::string GameObject::MapKeyMetaMapIdentifier = "meta_map_identifier";

const std::vector<std::string> GameObject::AttributeKeys =
{
	GameObject::MapKeyId,
	GameObject::MapKeyName,
	GameObject::MapKeyType,
	GameObject::MapKeyXPosition,
	GameObject::MapKeyYPosition,
	GameObject::MapKeyWidth,
	GameObject::MapKeyHeight,
	GameObject::MapKeyRotation,
};

const std::string GameObject::MapKeyPropertyName = "name";
const std::string GameObject::MapKeyPropertyType = "type";
const std::string GameObject::MapKeyPropertyValue = "value";

GameObject::GameObject() : GameObject(ValueMap())
{
}

GameObject::GameObject(const ValueMap& properties) : super()
{
	this->properties = properties;
	this->zSorted = false;
	this->tags = std::set<std::string>();
	this->polylinePoints = std::vector<Vec2>();
	this->stateVariables = ValueMap();
	this->listenEvent = GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyListenEvent, Value("")).asString();
	this->sendEvent = GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeySendEvent, Value("")).asString();
	this->uniqueIdentifier = "";
	this->attachedBehavior = std::vector<AttachedBehavior*>();
	this->attachedBehaviorNode = Node::create();
	this->setPosition(Vec2::ZERO);
	this->addTag(GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyTag, Value("")).asString());

	std::vector<std::string> tags = StrUtils::splitOn(GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyTags, Value("")).asString(), ", ", false);

	for (auto it = tags.begin(); it != tags.end(); it++)
	{
		this->addTag(*it);
	}

	if (GameUtils::keyExists(this->properties, GameObject::MapKeyMetaMapIdentifier))
	{
		this->uniqueIdentifier = (this->properties.at(GameObject::MapKeyMetaMapIdentifier).asString()) + "_" + (this->properties.at(GameObject::MapKeyId).asString());
	}

	// Map the coordinates of Tiled space to Cocos space for isometric games:
	if (GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyMetaIsIsometric, Value(false)).asBool())
	{
		this->setAnchorPoint(Vec2(0.5f, 0.0f));

		Size mapSize = Size(
			GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyMetaMapWidth, Value(0.0f)).asFloat(),
			GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyMetaMapHeight, Value(0.0f)).asFloat()
		);

		Vec2 position = Vec2(
			GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyXPosition, Value(0.0f)).asFloat(),
			GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyYPosition, Value(0.0f)).asFloat()
		);

		Size objectSize = Size(
			GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyWidth, Value(0.0f)).asFloat(),
			GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyHeight, Value(0.0f)).asFloat()
		);

		// Isometric position to screen position conversion magic
		Vec2 convertedPosition = Vec2(
			(position.x + position.y) + objectSize.width,
			(position.y - position.x) / 2.0f + mapSize.height / 2.0f
		);

		this->setPosition(convertedPosition);

		// Parse any polyline points in iso space
		ValueVector polygonPointsRaw = GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyPolyLinePoints, Value(ValueVector())).asValueVector();

		if (polygonPointsRaw.empty())
		{
			polygonPointsRaw = GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyPoints, Value(ValueVector())).asValueVector();
		}
		
		for (auto it = polygonPointsRaw.begin(); it != polygonPointsRaw.end(); ++it)
		{
			ValueMap point = it->asValueMap();

			Vec2 delta = Vec2(
				point.at(GameObject::MapKeyXPosition).asFloat(),
				point.at(GameObject::MapKeyYPosition).asFloat()
			);

			// Convert to iso space
			Vec2 convertedDelta = Vec2(
				(delta.x + delta.y),
				(delta.y - delta.x) / 2.0f
			);

			this->polylinePoints.push_back(convertedDelta);
		}
	}
	// Map the coordinates of Tiled space to Cocos space for 2d games:
	else
	{
		Size mapSize = Size(
			GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyWidth, Value(0.0f)).asFloat(),
			GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyHeight, Value(0.0f)).asFloat()
		);

		// Note: Explicit checks for key for setting position. Important, because non-deserialized objects may not have this key, and should end up at (0, 0)
		if (GameUtils::keyExists(this->properties, GameObject::MapKeyXPosition))
		{
			this->setPositionX(GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyXPosition, Value(0.0f)).asFloat() + mapSize.width / 2.0f);
		}

		if (GameUtils::keyExists(this->properties, GameObject::MapKeyYPosition))
		{
			this->setPositionY(GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyYPosition, Value(0.0f)).asFloat() + mapSize.height / 2.0f);
		}

		// Parse any polyline points in cocos space
		ValueVector polygonPointsRaw = GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyPolyLinePoints, Value(ValueVector())).asValueVector();

		if (polygonPointsRaw.empty())
		{
			polygonPointsRaw = GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyPoints, Value(ValueVector())).asValueVector();
		}

		for (auto it = polygonPointsRaw.begin(); it != polygonPointsRaw.end(); ++it)
		{
			ValueMap point = it->asValueMap();

			Vec2 delta = Vec2(
				point.at(GameObject::MapKeyXPosition).asFloat(),
				point.at(GameObject::MapKeyYPosition).asFloat()
			);

			// Negate the Y since we're operating in a different coordinate space
			Vec2 convertedDelta = Vec2(
				delta.x,
				-delta.y
			);

			this->polylinePoints.push_back(convertedDelta);
		}
	}

	this->addChild(this->attachedBehaviorNode);
}

GameObject::~GameObject()
{
}

void GameObject::onEnter()
{
	super::onEnter();

	this->loadObjectState();
}

void GameObject::initializeListeners()
{
	super::initializeListeners();
	
	this->addEventListenerIgnorePause(EventListenerCustom::create(ObjectEvents::EventQueryObject, [=](EventCustom* eventCustom)
	{
		QueryObjectsArgsBase* args = static_cast<QueryObjectsArgsBase*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			args->tryInvoke(this);
		}
	}));

	for (auto it = this->tags.begin(); it != this->tags.end(); it++)
	{
		this->addEventListenerIgnorePause(EventListenerCustom::create(ObjectEvents::EventQueryObjectByTagPrefix + *it, [=](EventCustom* eventCustom)
		{
			QueryObjectsArgsBase* args = static_cast<QueryObjectsArgsBase*>(eventCustom->getUserData());

			if (args != nullptr)
			{
				args->tryInvoke(this);
			}
		}));
	}
}

std::string GameObject::getUniqueIdentifier()
{
	return this->uniqueIdentifier;
}

void GameObject::attachBehavior(AttachedBehavior* attachedBehavior)
{
	if (attachedBehavior == nullptr || attachedBehavior->isInvalidated())
	{
		return;
	}

	this->attachedBehavior.push_back(attachedBehavior);
	this->attachedBehaviorNode->addChild(attachedBehavior);
}

void GameObject::setState(std::string key, Value value, bool broadcastUpdate)
{
	this->stateVariables[key] = value;

	if (broadcastUpdate)
	{
		ObjectEvents::TriggerWriteObjectState(ObjectEvents::StateWriteArgs(this, key, value));
	}
}

void GameObject::addTag(std::string tag)
{
	if (tag.empty())
	{
		return;
	}
	
	this->tags.insert(tag);
}

Value GameObject::getPropertyOrDefault(std::string key, Value value)
{
	return GameUtils::getKeyOrDefault(this->properties, key, value);
}

Value GameObject::getStateOrDefault(std::string key, Value value)
{
	return GameUtils::getKeyOrDefault(this->stateVariables, key, value);
}

int GameObject::getStateOrDefaultInt(std::string key, int value)
{
	return GameUtils::getKeyOrDefault(this->stateVariables, key, Value(value)).asInt();
}

float GameObject::getStateOrDefaultFloat(std::string key, float value)
{
	return GameUtils::getKeyOrDefault(this->stateVariables, key, Value(value)).asFloat();
}

bool GameObject::getStateOrDefaultBool(std::string key, bool value)
{
	return GameUtils::getKeyOrDefault(this->stateVariables, key, Value(value)).asBool();
}

bool GameObject::hasState(std::string key)
{
	return GameUtils::keyExists(this->stateVariables, key);
}

void GameObject::clearState(std::string key)
{
	GameUtils::deleteKey(this->stateVariables, key);
}

void GameObject::setZSorted(bool zSorted)
{
	this->zSorted = zSorted;
}

bool GameObject::isZSorted()
{
	return this->zSorted;
}

bool GameObject::isMapObject()
{
	return this->uniqueIdentifier != "";
}

void GameObject::saveObjectState(std::string uniqueIdentifier, std::string key, cocos2d::Value value)
{
	ValueMap saveData = SaveManager::getProfileDataOrDefault(uniqueIdentifier, Value(ValueMap())).asValueMap();

	saveData[key] = value;

	SaveManager::saveProfileData(uniqueIdentifier, Value(saveData));
}

void GameObject::saveObjectState(std::string key, cocos2d::Value value)
{
	if (this->isMapObject())
	{
		this->saveProperties[key] = value;

		SaveManager::saveProfileData(this->uniqueIdentifier, Value(this->saveProperties));
	}
}

const Value& GameObject::getObjectStateOrDefault(std::string key, const Value& defaultValue)
{
	return GameUtils::getKeyOrDefault(this->saveProperties, key, defaultValue);
}

void GameObject::loadObjectState()
{
	if (this->isMapObject())
	{
		this->saveProperties = SaveManager::getProfileDataOrDefault(this->uniqueIdentifier, Value(ValueMap())).asValueMap();
		this->onObjectStateLoaded();
	}
}


void GameObject::listenForStateWrite(std::string key, std::function<void(cocos2d::Value)> onWrite)
{
	const std::string eventKey = key + "_" + std::to_string((unsigned long long)(this));

	this->addEventListenerIgnorePause(EventListenerCustom::create(ObjectEvents::EventWriteStatePrefix + eventKey, [=](EventCustom* eventCustom)
	{
		ObjectEvents::StateWriteArgs* args = static_cast<ObjectEvents::StateWriteArgs*>(eventCustom->getUserData());
		
		if (args != nullptr)
		{
			onWrite(args->value);
		}
	}));
}

void GameObject::listenForStateWriteOnce(std::string key, std::function<void(cocos2d::Value)> onWrite)
{
	static unsigned int UniqueCounter = 0;
	const std::string eventKey = key + "_" + std::to_string((unsigned long long)(this));
	const std::string uniqueKey = eventKey + "_" + std::to_string(UniqueCounter++);

	EventListener* listener = EventListenerCustom::create(ObjectEvents::EventWriteStatePrefix + eventKey, [=](EventCustom* eventCustom)
	{
		ObjectEvents::StateWriteArgs* args = static_cast<ObjectEvents::StateWriteArgs*>(eventCustom->getUserData());
		
		if (args != nullptr)
		{
			this->removeEventListenerByTag(uniqueKey);
			
			onWrite(args->value);
		}
	});

	listener->setTag(uniqueKey);

	this->addEventListenerIgnorePause(listener);
}

void GameObject::onObjectStateLoaded()
{
}

bool GameObject::containsAttributes()
{
	for (auto it = GameObject::AttributeKeys.begin(); it != GameObject::AttributeKeys.end(); it++)
	{
		if (GameUtils::keyExists(this->properties, *it))
		{
			return true;
		}
	}

	return false;
}

bool GameObject::containsProperties()
{
	for (auto it = this->properties.begin(); it != this->properties.end(); it++)
	{
		if (!GameObject::isAttributeOrHiddenProperty(it->first))
		{
			return true;
		}
	}

	return false;
}

bool GameObject::isAttributeOrHiddenProperty(std::string propertyName)
{
	if (propertyName == GameObject::MapKeyGid || propertyName == GameObject::MapKeyPoints)
	{
		return true;
	}

	return std::find(GameObject::AttributeKeys.begin(), GameObject::AttributeKeys.end(), propertyName) != GameObject::AttributeKeys.end();
}

void GameObject::broadcastMapEvent(std::string eventName, cocos2d::ValueMap args)
{
	if (eventName.empty())
	{
		return;
	}
	
	ObjectEvents::TriggerBroadCastMapObjectState(eventName, args);
}

void GameObject::listenForMapEvent(std::string eventName, std::function<void(ValueMap args)> callback)
{
	if (eventName.empty())
	{
		return;
	}

	this->addEventListenerIgnorePause(EventListenerCustom::create(ObjectEvents::EventBroadCastMapObjectStatePrefix + eventName, [=](EventCustom* eventCustom)
	{
		ValueMap* args = static_cast<ValueMap*>(eventCustom->getUserData());

		callback(*args);
	}));
}

std::string GameObject::getListenEvent()
{
	return this->listenEvent;
}

std::string GameObject::getSendEvent()
{
	return this->sendEvent;
}

void GameObject::despawn()
{
	this->attachedBehaviorNode->removeAllChildren();

	ObjectEvents::TriggerObjectDespawning(ObjectEvents::ObjectDespawningArgs(this));

	if (this->getParent() != nullptr)
	{
		this->getParent()->removeChild(this);
	}
}

void GameObject::onDespawn(std::function<void()> callback)
{
	if (callback == nullptr)
	{
		return;
	}
	
	this->addEventListenerIgnorePause(EventListenerCustom::create(ObjectEvents::EventObjectDespawningPrefix + std::to_string((unsigned long long)(this)), [=](EventCustom* eventCustom)
	{
		callback();
	}));
}
