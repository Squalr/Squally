#pragma once
#include <functional>
#include <string>

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

namespace cocos2d
{
	class Value;
	typedef std::map<std::string, Value> ValueMap;
}

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
	static const std::string EventQueryObject;
	static const std::string EventBroadCastMapObjectStatePrefix;

	static void TriggerBroadCastMapObjectState(std::string eventName, cocos2d::ValueMap args);

	template<class T>
	static void QueryObjects(QueryObjectsArgs<T> args)
	{
		cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
			ObjectEvents::EventQueryObject,
			&args
		);
	}
};
