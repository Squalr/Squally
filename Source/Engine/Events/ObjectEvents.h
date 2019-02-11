#pragma once
#include <functional>
#include <string>

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

class SerializableObject;

class QueryObjectsArgsBase
{
public:
	virtual void tryInvoke(SerializableObject* object) = 0;
};

template<class T>
class QueryObjectsArgs : QueryObjectsArgsBase
{
public:
	std::function<void(T*)> onObjectQueriedCallback;

	QueryObjectsArgs(std::function<void(T*)> onObjectQueriedCallback) : onObjectQueriedCallback(onObjectQueriedCallback)
	{
	}

	void tryInvoke(SerializableObject* object) override
	{
		if (dynamic_cast<T*>(object) != nullptr)
		{
			this->onObjectQueriedCallback((T*)object);
		}
	}
};

class ObjectEvents
{
public:
	static const std::string EventQueryObject;

	template<class T>
	static void QueryObjects(QueryObjectsArgs<T> args)
	{
		cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
			ObjectEvents::EventQueryObject,
			&args
		);
	}
};
