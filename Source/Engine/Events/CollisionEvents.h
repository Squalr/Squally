#pragma once
#include <functional>
#include <string>

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"
#include "cocos/base/CCValue.h"

class SmartNode;

class QueryCollisionObjectsArgsBase
{
public:
	virtual void tryInvoke(SmartNode* object) = 0;
};

template<class T>
class QueryCollisionObjectsArgs : QueryCollisionObjectsArgsBase
{
public:
	std::function<void(T*)> onObjectQueriedCallback;
	std::function<void(T*, bool*)> onObjectQueriedCallbackWithHandled;
	bool isHandled;

	QueryCollisionObjectsArgs(std::function<void(T*)> onObjectQueriedCallback) : onObjectQueriedCallback(onObjectQueriedCallback), onObjectQueriedCallbackWithHandled(nullptr), isHandled(false)
	{
	}

	QueryCollisionObjectsArgs(std::function<void(T*, bool*)> onObjectQueriedCallbackWithHandled) : onObjectQueriedCallback(nullptr), onObjectQueriedCallbackWithHandled(onObjectQueriedCallbackWithHandled), isHandled(false)
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

class CollisionEvents
{
public:
	static const std::string EventQueryCollisionObject;

	template<class T>
	static void QueryObjects(QueryCollisionObjectsArgs<T> args, int bitmask)
	{
		cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
			CollisionEvents::EventQueryCollisionObject,
			&args
		);
	}
};
