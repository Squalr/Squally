#include "GameObject.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
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
const std::string GameObject::MapKeyDepth = "depth";
const std::string GameObject::MapKeyScale = "scale";
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
const std::string GameObject::MapKeyQueryable = "args";
const std::string GameObject::MapKeyRotation = "rotation";
const std::string GameObject::MapKeyPoints = "points";
const std::string GameObject::MapKeyPolyLinePoints = "polylinePoints";
const std::string GameObject::MapKeyZoom = "zoom";

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

const std::string GameObject::PropertyName = "name";
const std::string GameObject::PropertyType = "type";
const std::string GameObject::PropertyValue = "value";
unsigned long long GameObject::WatchId = 0;

GameObject::GameObject() : GameObject(ValueMap())
{
}

GameObject::GameObject(const ValueMap& properties) : super()
{
	this->properties = properties;
	this->zSorted = false;
	this->despawned = false;
	this->tags = std::set<std::string>();
	this->polylinePoints = std::vector<Vec2>();
	this->stateVariables = ValueMap();
	this->listenEvent = GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyListenEvent, Value("")).asString();
	this->sendEvent = GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeySendEvent, Value("")).asString();
	this->uniqueIdentifier = "";
	this->attachedBehavior = std::vector<AttachedBehavior*>();

	std::vector<std::string> tags = StrUtils::splitOn(GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyTags, Value("")).asString(), ", ", false);

	if (GameUtils::keyExists(this->properties, GameObject::MapKeyMetaMapIdentifier))
	{
		this->uniqueIdentifier = GameObject::BuildUUID(this->properties.at(GameObject::MapKeyMetaMapIdentifier).asString(), this->properties.at(GameObject::MapKeyId).asString());
	}
	
	this->addTag(GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyTag, Value("")).asString());
	this->addTag(GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyName, Value("")).asString());
	this->addTag(this->getUniqueIdentifier());

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
		
		for (auto next : polygonPointsRaw)
		{
			ValueMap point = next.asValueMap();

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

		for (auto next : polygonPointsRaw)
		{
			ValueMap point = next.asValueMap();

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

	this->setPositionZ(GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyDepth, Value(0.0f)).asFloat());
	this->loadObjectState();
}

GameObject::~GameObject()
{
}

void GameObject::onEnter()
{
	super::onEnter();
}

void GameObject::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();
}

void GameObject::initializeListeners()
{
	super::initializeListeners();
	
	this->addEventListenerIgnorePause(EventListenerCustom::create(ObjectEvents::EventQueryObject, [=](EventCustom* eventCustom)
	{
		QueryObjectsArgsBase* args = static_cast<QueryObjectsArgsBase*>(eventCustom->getData());

		if (args != nullptr && GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyQueryable, Value(true)).asBool())
		{
			args->tryInvoke(this);
		}
	}));

	for (auto tag : this->tags)
	{
		this->addEventListenerIgnorePause(EventListenerCustom::create(ObjectEvents::EventQueryObjectByTagPrefix + tag, [=](EventCustom* eventCustom)
		{
			QueryObjectsArgsBase* args = static_cast<QueryObjectsArgsBase*>(eventCustom->getData());

			if (args != nullptr && GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyQueryable, Value(true)).asBool())
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
	if (this->isDespawned() || attachedBehavior == nullptr || attachedBehavior->isInvalidated())
	{
		return;
	}

	this->attachedBehavior.push_back(attachedBehavior);
	this->addChild(attachedBehavior);
}

void GameObject::detachAllBehavior()
{
	if (this->isDespawned())
	{
		return;
	}

	for (auto next : this->attachedBehavior)
	{
		next->onDisable();
	}

	this->attachedBehavior.clear();
}

void GameObject::detachBehavior(AttachedBehavior* attachedBehavior)
{
	if (this->isDespawned() || attachedBehavior == nullptr)
	{
		return;
	}

	if (std::find(this->attachedBehavior.begin(), this->attachedBehavior.end(), attachedBehavior) != this->attachedBehavior.end())
	{
		this->attachedBehavior.erase(std::remove(this->attachedBehavior.begin(), this->attachedBehavior.end(), attachedBehavior), this->attachedBehavior.end());

		// Note: Removing children at runtime is unsafe. The best we can do is disable it.
		attachedBehavior->onDisable();
	}
}

void GameObject::setState(std::string key, Value value, bool broadcastUpdate)
{
	this->stateVariables[key] = value;

	if (broadcastUpdate)
	{
		ObjectEvents::TriggerWriteObjectState(StateWriteArgs(this, key, value));
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

Value GameObject::getRuntimeStateOrDefault(std::string key, Value value)
{
	return GameUtils::getKeyOrDefault(this->stateVariables, key, value);
}

int GameObject::getRuntimeStateOrDefaultInt(std::string key, int value)
{
	return GameUtils::getKeyOrDefault(this->stateVariables, key, Value(value)).asInt();
}

float GameObject::getRuntimeStateOrDefaultFloat(std::string key, float value)
{
	return GameUtils::getKeyOrDefault(this->stateVariables, key, Value(value)).asFloat();
}

bool GameObject::getRuntimeStateOrDefaultBool(std::string key, bool value)
{
	return GameUtils::getKeyOrDefault(this->stateVariables, key, Value(value)).asBool();
}

ValueMap& GameObject::getStateVariables()
{
	return this->stateVariables;
}

bool GameObject::hasRuntimeState(std::string key)
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
	return !this->uniqueIdentifier.empty();
}

void GameObject::saveObjectState(std::string key, cocos2d::Value value)
{
	if (this->isMapObject())
	{
		this->saveProperties[key] = value;

		SaveManager::SaveProfileData(this->uniqueIdentifier, Value(this->saveProperties));
	}
}

void GameObject::saveObjectState(std::string uniqueIdentifier, std::string key, cocos2d::Value value)
{
	ValueMap saveData = SaveManager::GetProfileDataOrDefault(uniqueIdentifier, Value(ValueMap())).asValueMap();

	saveData[key] = value;

	SaveManager::SaveProfileData(uniqueIdentifier, Value(saveData));
}

void GameObject::saveTemporalObjectState(std::string key, cocos2d::Value value)
{
	// TODO: Implement temporal state, passing temporal flags (map temporal, time temporal, zone temporal, etc)
	if (this->isMapObject())
	{
		this->saveProperties[key] = value;

		SaveManager::SaveProfileData(this->uniqueIdentifier, Value(this->saveProperties));
	}
}

void GameObject::saveTemporalObjectState(std::string uniqueIdentifier, std::string key, cocos2d::Value value)
{
	// TODO: Implement temporal state, passing temporal flags (map temporal, time temporal, zone temporal, etc)
	ValueMap saveData = SaveManager::GetProfileDataOrDefault(uniqueIdentifier, Value(ValueMap())).asValueMap();

	saveData[key] = value;

	SaveManager::SaveProfileData(uniqueIdentifier, Value(saveData));
}

const Value& GameObject::loadObjectStateOrDefault(std::string key, const Value& defaultValue)
{
	return GameUtils::getKeyOrDefault(this->saveProperties, key, defaultValue);
}

void GameObject::loadObjectState()
{
	if (this->isMapObject())
	{
		this->saveProperties = SaveManager::GetProfileDataOrDefault(this->uniqueIdentifier, Value(ValueMap())).asValueMap();
	}
}


void GameObject::listenForStateWrite(std::string key, std::function<void(cocos2d::Value)> onWrite)
{
	const std::string eventKey = key + "_" + std::to_string((unsigned long long)(this));

	this->addEventListenerIgnorePause(EventListenerCustom::create(ObjectEvents::EventWriteStatePrefix + eventKey, [=](EventCustom* eventCustom)
	{
		StateWriteArgs* args = static_cast<StateWriteArgs*>(eventCustom->getData());
		
		if (args != nullptr)
		{
			onWrite(args->value);
		}
	}));
}

void GameObject::listenForStateWriteOnce(std::string key, std::function<void(cocos2d::Value)> onWrite)
{
	const std::string eventKey = key + "_" + std::to_string((unsigned long long)(this));

	EventListenerCustom* listener = EventListenerCustom::create(ObjectEvents::EventWriteStatePrefix + eventKey, nullptr);

	listener->setCallback([=](EventCustom* eventCustom)
	{
		StateWriteArgs* args = static_cast<StateWriteArgs*>(eventCustom->getData());
		
		if (args != nullptr)
		{
			this->removeEventListener(listener);
			
			onWrite(args->value);
		}
	});

	this->addEventListenerIgnorePause(listener);
}

bool GameObject::containsAttributes()
{
	for (auto next : GameObject::AttributeKeys)
	{
		if (GameUtils::keyExists(this->properties, next))
		{
			return true;
		}
	}

	return false;
}

bool GameObject::containsProperties()
{
	for (auto next : this->properties)
	{
		if (!GameObject::isAttributeOrHiddenProperty(next.first))
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
		ValueMap* args = static_cast<ValueMap*>(eventCustom->getData());

		if (args != nullptr && callback != nullptr)
		{
			callback(*args);
		}
	}));
}

void GameObject::listenForMapEventOnce(std::string eventName, std::function<void(cocos2d::ValueMap args)> callback)
{
	if (eventName.empty())
	{
		return;
	}
	
	const std::string eventKey = eventName + "_" + std::to_string((unsigned long long)(this));

	EventListenerCustom* listener = EventListenerCustom::create(ObjectEvents::EventBroadCastMapObjectStatePrefix + eventName, nullptr);
	
	listener->setCallback([=](EventCustom* eventCustom)
	{
		ValueMap* args = static_cast<ValueMap*>(eventCustom->getData());
		
		if (args != nullptr && callback != nullptr)
		{
			this->removeEventListener(listener);
			callback(*args);
		}
	});

	this->addEventListenerIgnorePause(listener);
}

std::string GameObject::getListenEvent()
{
	return this->listenEvent;
}

std::string GameObject::getSendEvent()
{
	return this->sendEvent;
}

void GameObject::despawn(float despawnDelay)
{
	if (despawnDelay <= 0.0f)
	{
		this->onDespawn();
	}
	else
	{
		this->runAction(Sequence::create(
			DelayTime::create(despawnDelay),
			CallFunc::create([=]()
			{
				this->onDespawn();
			}),
			nullptr
		));
	}
}

void GameObject::onDespawn()
{
	std::vector<AttachedBehavior*> behaviorClone = this->attachedBehavior;

	for (auto behavior : behaviorClone)
	{
		this->detachBehavior(behavior);
	}
	
	this->removeAllListeners();
	this->unscheduleUpdate();
	this->setVisible(false);
	this->despawned = true;
}

bool GameObject::isDespawned()
{
	return this->despawned;
}

std::string GameObject::BuildUUID(std::string mapId, std::string objectId)
{
	return mapId + "_" + objectId;
}