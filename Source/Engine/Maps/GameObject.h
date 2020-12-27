#pragma once
#include <string>

#include "cocos/math/CCGeometry.h"

#include "Engine/AttachedBehavior/AttachedBehavior.h"
#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Value;
	typedef std::map<std::string, cocos2d::Value> ValueMap;
}

class GameObject : public SmartNode
{
public:
	std::string getUniqueIdentifier();
	void attachBehavior(AttachedBehavior* attachedBehavior);
	void detachAllBehavior();
	void detachBehavior(AttachedBehavior* attachedBehavior);
	void setState(std::string key, cocos2d::Value value, bool broadcastUpdate = true);
	void addTag(std::string tag);
	cocos2d::Value getPropertyOrDefault(std::string key, cocos2d::Value value);
	cocos2d::Value getRuntimeStateOrDefault(std::string key, cocos2d::Value value);
	int getRuntimeStateOrDefaultInt(std::string key, int value);
	float getRuntimeStateOrDefaultFloat(std::string key, float value);
	bool getRuntimeStateOrDefaultBool(std::string key, bool value);
	cocos2d::ValueMap& getStateVariables();
	bool hasRuntimeState(std::string key);
	void clearState(std::string key);
	void setZSorted(bool zSorted);
	bool isZSorted();
	void listenForStateWrite(std::string key, std::function<void(cocos2d::Value)> onWrite);
	void listenForStateWriteOnce(std::string key, std::function<void(cocos2d::Value)> onWrite);
	void saveObjectState(std::string key, cocos2d::Value value);
	static void saveObjectState(std::string uniqueIdentifier, std::string key, cocos2d::Value value);
	void saveTemporalObjectState(std::string key, cocos2d::Value value);
	static void saveTemporalObjectState(std::string uniqueIdentifier, std::string key, cocos2d::Value value);
	const cocos2d::Value& loadObjectStateOrDefault(std::string key, const cocos2d::Value& defaultValue);
	void broadcastMapEvent(std::string eventName, cocos2d::ValueMap args);
	void listenForMapEvent(std::string eventName, std::function<void(cocos2d::ValueMap args)> callback);
	void listenForMapEventOnce(std::string eventName, std::function<void(cocos2d::ValueMap args)> callback);
	std::string getListenEvent();
	std::string getSendEvent();
	void despawn(float despawnDelay = 0.0f);
	bool isDespawned();

	template <class T>
	T* getAttachedBehavior()
	{
		for (auto next : attachedBehavior)
		{
			if (dynamic_cast<T*>(next) != nullptr && next->isQueryable())
			{
				return dynamic_cast<T*>(next);
			}
		}

		return nullptr;
	}

	template <class T>
	void getAttachedBehavior(std::function<void(T*)> onFound)
	{
		T* attachedBehavior = this->getAttachedBehavior<T>();

		if (attachedBehavior != nullptr && onFound != nullptr)
		{
			onFound(attachedBehavior);
		}
	}
	
	static unsigned long long WatchId;

	template <class T>
	void watchForAttachedBehavior(std::function<void(T*)> onBehaviorFound)
	{
		unsigned long long watchId = GameObject::WatchId++;
		std::string eventKey = "EVENT_WATCH_FOR_ATTACHED_BEHAVIOR_" + std::to_string(watchId);

		// Do an immediate check for the object
		T* behavior = this->getAttachedBehavior<T>();

		if (behavior != nullptr)
		{
			onBehaviorFound(behavior);
			return;
		}

		// Schedule a task to watch for the object
		this->schedule([=](float dt)
		{
			T* behavior = this->getAttachedBehavior<T>();

			if (behavior != nullptr)
			{
				this->unschedule(eventKey);
				onBehaviorFound(behavior);
			}
		}, eventKey);
	}

	static const std::string MapKeyId;
	static const std::string MapKeyName;
	static const std::string MapKeyTag;
	static const std::string MapKeyTags;
	static const std::string MapKeyPoints;
	static const std::string MapKeyPolyLinePoints;
	static const std::string MapKeyRotation;
	static const std::string MapKeyType;
	static const std::string MapKeyWidth;
	static const std::string MapKeyHeight;
	static const std::string MapKeyXPosition;
	static const std::string MapKeyYPosition;
	static const std::string MapKeyDepth;
	static const std::string MapKeyScale;
	static const std::string MapKeyFlipX;
	static const std::string MapKeyFlipY;
	static const std::string MapKeyRepeatX;
	static const std::string MapKeyRepeatY;
	static const std::string MapKeyListenEvent;
	static const std::string MapKeySendEvent;
	static const std::string MapKeyState;
	static const std::string MapKeyQuest;
	static const std::string MapKeyQuestLine;
	static const std::string MapKeyQuestTag;
	static const std::string MapKeyAttachedBehavior;
	static const std::string MapKeyAttachedBehaviorArgs;
	static const std::string MapKeyArgs;
	static const std::string MapKeyQueryable;
	static const std::string MapKeyZoom;

	static const std::string MapKeyGid;

	static const std::string MapKeyMetaIsIsometric;
	static const std::string MapKeyMetaMapHeight;
	static const std::string MapKeyMetaMapWidth;
	static const std::string MapKeyMetaMapIdentifier;

	static const std::vector<std::string> AttributeKeys;

	static const std::string PropertyName;
	static const std::string PropertyType;
	static const std::string PropertyValue;

	cocos2d::ValueMap properties;
	
protected:
	GameObject();
	GameObject(const cocos2d::ValueMap& properties);
	virtual ~GameObject();
	
	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void initializeListeners() override;
	virtual void onDespawn();
	bool isMapObject();
	void loadObjectState();
	static std::string BuildUUID(std::string mapId, std::string objectId);

	std::string listenEvent;
	std::string sendEvent;
	std::vector<cocos2d::Vec2> polylinePoints;

private:
	typedef SmartNode super;
	friend class MapLayer;
	
	bool isAttributeOrHiddenProperty(std::string propertyName);
	bool containsAttributes();
	bool containsProperties();

	bool despawned;
	std::set<std::string> tags;
	bool zSorted;
	std::string uniqueIdentifier;
	cocos2d::ValueMap saveProperties;
	cocos2d::ValueMap stateVariables;
	std::vector<AttachedBehavior*> attachedBehavior;
};
