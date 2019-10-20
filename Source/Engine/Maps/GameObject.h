#pragma once
#include <string>

#include "cocos/math/CCGeometry.h"

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class EventListener;
	class Value;
	typedef std::map<std::string, Value> ValueMap;
}

class AttachedBehavior;

class GameObject : public SmartNode
{
public:
	static void saveObjectState(std::string uniqueIdentifier, std::string key, cocos2d::Value value);
	std::string getUniqueIdentifier();
	void attachBehavior(AttachedBehavior* attachedBehavior);
	void setState(std::string key, cocos2d::Value value, bool broadcastUpdate = true);
	cocos2d::Value getStateOrDefault(std::string key, cocos2d::Value value);
	int getStateOrDefaultInt(std::string key, int value);
	float getStateOrDefaultFloat(std::string key, float value);
	bool getStateOrDefaultBool(std::string key, bool value);
	bool hasState(std::string key);
	void clearState(std::string key);
	void setZSorted(bool zSorted);
	bool isZSorted();
	void saveObjectState(std::string key, cocos2d::Value value);
	void listenForStateWrite(std::string key, std::function<void(cocos2d::Value)> onWrite);
	void listenForStateWriteOnce(std::string key, std::function<void(cocos2d::Value)> onWrite);
	const cocos2d::Value& getObjectStateOrDefault(std::string key, const cocos2d::Value& defaultValue);
	void broadcastMapEvent(std::string eventName, cocos2d::ValueMap args);
	void listenForMapEvent(std::string eventName, std::function<void(cocos2d::ValueMap args)> callback);
	std::string getListenEvent();
	std::string getSendEvent();
	void despawn();

	template <class T>
	T* getAttachedBehavior()
	{
		for (auto it = attachedBehavior.begin(); it != attachedBehavior.end(); it++)
		{
			if (dynamic_cast<T*>(*it) != nullptr)
			{
				return dynamic_cast<T*>(*it);
			}
		}

		return nullptr;
	}

	template <class T>
	void watchForAttachedBehavior(std::function<void(T*)> onBehaviorFound)
	{
		static unsigned long long WatchId = 0;
		unsigned long long watchId = WatchId++;
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

		}, 1.0f / 60.0f, 0, 0.0f, eventKey);
	}

	static const std::string MapKeyId;
	static const std::string MapKeyName;
	static const std::string MapKeyTag;
	static const std::string MapKeyPoints;
	static const std::string MapKeyPolyLinePoints;
	static const std::string MapKeyRotation;
	static const std::string MapKeyType;
	static const std::string MapKeyWidth;
	static const std::string MapKeyHeight;
	static const std::string MapKeyXPosition;
	static const std::string MapKeyYPosition;
	static const std::string MapKeyScale;
	static const std::string MapKeyScaleX;
	static const std::string MapKeyScaleY;
	static const std::string MapKeyAutoScale;
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

	static const std::string MapKeyGid;

	static const std::string MapKeyMetaIsIsometric;
	static const std::string MapKeyMetaMapHeight;
	static const std::string MapKeyMetaMapWidth;
	static const std::string MapKeyMetaMapIdentifier;

	static const std::vector<std::string> AttributeKeys;

	static const std::string MapKeyPropertyName;
	static const std::string MapKeyPropertyType;
	static const std::string MapKeyPropertyValue;

protected:
	GameObject();
	GameObject(const cocos2d::ValueMap& properties);
	virtual ~GameObject();
	
	void onEnter() override;
	void initializeListeners() override;
	bool isMapObject();
	void loadObjectState();
	virtual void onObjectStateLoaded();

	cocos2d::ValueMap properties;
	std::string listenEvent;
	std::string sendEvent;
	std::vector<cocos2d::Vec2> polylinePoints;

private:
	typedef SmartNode super;
	bool isAttributeOrHiddenProperty(std::string propertyName);
	bool containsAttributes();
	bool containsProperties();

	std::string tag;
	bool zSorted;
	cocos2d::Node* attachedBehaviorNode;
	std::string uniqueIdentifier;
	cocos2d::ValueMap saveProperties;
	cocos2d::ValueMap stateVariables;
	std::vector<AttachedBehavior*> attachedBehavior;
};
