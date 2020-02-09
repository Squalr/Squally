#pragma once
#include <functional>
#include <string>

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"
#include "cocos/base/CCValue.h"

class UIBoundObject;
class MapLayer;
class GameObject;
class SmartNode;

class QueryObjectsArgsBase
{
public:
	virtual void tryInvoke(SmartNode* object) = 0;
};

template<class T>
class QueryObjectsArgs : QueryObjectsArgsBase
{
public:
	std::function<void(T*)> onObjectQueriedCallback;
	std::function<void(T*, bool*)> onObjectQueriedCallbackWithHandled;
	bool isHandled;

	QueryObjectsArgs(std::function<void(T*)> onObjectQueriedCallback) : onObjectQueriedCallback(onObjectQueriedCallback), onObjectQueriedCallbackWithHandled(nullptr), isHandled(false)
	{
	}

	QueryObjectsArgs(std::function<void(T*, bool*)> onObjectQueriedCallbackWithHandled) : onObjectQueriedCallback(nullptr), onObjectQueriedCallbackWithHandled(onObjectQueriedCallbackWithHandled), isHandled(false)
	{
	}

	void tryInvoke(SmartNode* object) override
	{
		if (dynamic_cast<T*>(object) != nullptr)
		{
			if (onObjectQueriedCallback != nullptr)
			{
				this->onObjectQueriedCallback((T*)object);
			}
			else if (onObjectQueriedCallbackWithHandled != nullptr && !this->isHandled)
			{
				this->onObjectQueriedCallbackWithHandled((T*)object, &this->isHandled);
			}
		}
	}
};

class ObjectEvents
{
public:
	static const std::string EventCollisonMapUpdated;
	static const std::string EventQueryObject;
	static const std::string EventQueryObjectByTagPrefix;
	static const std::string EventBroadCastMapObjectStatePrefix;
	static const std::string EventSpawnObject;
	static const std::string EventSpawnObjectDelegator;
	static const std::string EventObjectDespawningPrefix;
	static const std::string EventBindObjectToUI;
	static const std::string EventReparentBindPrefix;
	static const std::string EventElevateObject;
	static const std::string EventUnbindObjectPrefix;
	static const std::string EventWriteStatePrefix;

	enum class SpawnMethod
	{
		Below,
		Above,
		TopMost,
	};

	enum class PositionMode
	{
		Discard,
		Retain,
		SetToOwner,
	};

	struct RequestObjectSpawnArgs
	{
		cocos2d::Node* spawner;
		cocos2d::Node* objectToSpawn;
		SpawnMethod spawnMethod;
		PositionMode positionMode;
		std::function<void()> onSpawnSuccess;
		std::function<void()> onSpawnFailed;
		
		bool handled;

		RequestObjectSpawnArgs() : spawner(nullptr), objectToSpawn(nullptr), spawnMethod(SpawnMethod::Above), onSpawnSuccess(nullptr), onSpawnFailed(nullptr), handled(false) { }
		RequestObjectSpawnArgs(cocos2d::Node* spawner, cocos2d::Node* objectToSpawn, SpawnMethod spawnMethod, PositionMode positionMode, std::function<void()> onSpawnSuccess, std::function<void()> onSpawnFailed)
			: spawner(spawner), objectToSpawn(objectToSpawn), spawnMethod(spawnMethod), positionMode(positionMode), onSpawnSuccess(onSpawnSuccess), onSpawnFailed(onSpawnFailed), handled(false) { }
	};

	struct RequestObjectSpawnDelegatorArgs
	{
		MapLayer* sourceLayer;
		RequestObjectSpawnArgs* innerArgs;

		RequestObjectSpawnDelegatorArgs() : sourceLayer(nullptr), innerArgs(nullptr) { }
		RequestObjectSpawnDelegatorArgs(MapLayer* sourceLayer, RequestObjectSpawnArgs* innerArgs) : sourceLayer(sourceLayer), innerArgs(innerArgs) { }
	};

	struct RelocateObjectArgs
	{
		cocos2d::Node* relocatedObject;

		RelocateObjectArgs() : relocatedObject(nullptr) { }
		RelocateObjectArgs(cocos2d::Node* relocatedObject) : relocatedObject(relocatedObject) { }
	};

	struct ReparentBindArgs
	{
		cocos2d::Node* relocatedObject;
		cocos2d::Node* newParent;

		ReparentBindArgs() : relocatedObject(nullptr), newParent(nullptr) { }
		ReparentBindArgs(cocos2d::Node* relocatedObject, cocos2d::Node* newParent) : relocatedObject(relocatedObject), newParent(newParent) { }
	};

	struct StateWriteArgs
	{
		GameObject* owner;
		std::string key;
		cocos2d::Value value;

		StateWriteArgs(GameObject* owner, std::string key, cocos2d::Value value) : owner(owner), key(key), value(value) { }
	};

	static void TriggerCollisionMapUpdated();
	static void TriggerBroadCastMapObjectState(std::string eventName, cocos2d::ValueMap args);
	static void TriggerBindObjectToUI(RelocateObjectArgs args);
	static void TriggerReparentBind(ReparentBindArgs args);
	static void TriggerElevateObject(RelocateObjectArgs args);
	static void TriggerObjectSpawn(RequestObjectSpawnArgs args);
	static void TriggerObjectSpawnDelegator(RequestObjectSpawnDelegatorArgs args);
	static void TriggerWriteObjectState(StateWriteArgs args);

	template<class T>
	static void QueryObjects(QueryObjectsArgs<T> args, std::string tag = "")
	{
		if (tag.empty())
		{
			cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
				ObjectEvents::EventQueryObject,
				&args
			);
		}
		else
		{
			cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
				ObjectEvents::EventQueryObjectByTagPrefix + tag,
				&args
			);
		}
	}

	static unsigned long long WatchId;

	template <class T>
	static void watchForObject(cocos2d::Node* host, std::function<void(T*)> onObjectFound, std::string tag = "")
	{
		unsigned long long watchId = ObjectEvents::WatchId++;
		std::string eventKey = "EVENT_WATCH_FOR_OBJECT_" + std::to_string(watchId);

		bool wasHandled = false;

		// Do an immediate check for the object
		ObjectEvents::QueryObjects(QueryObjectsArgs<T>([&](T* object, bool* handled)
		{
			onObjectFound(object);
			*handled = true;
			wasHandled = true;
		}), tag);

		if (wasHandled)
		{
			return;
		}

		// Schedule a task to watch for the object
		host->schedule([=](float dt)
		{
			ObjectEvents::QueryObjects(QueryObjectsArgs<T>([&](T* object, bool* handled)
			{
				host->unschedule(eventKey);
				onObjectFound(object);
				*handled = true;
			}), tag);

		}, 1.0f / 60.0f, CC_REPEAT_FOREVER, 0.0f, eventKey);
	}
};
