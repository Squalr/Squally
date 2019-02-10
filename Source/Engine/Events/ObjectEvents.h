#pragma once
#include <functional>
#include <string>
#include <typeinfo>

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

class SerializableObject;

class ObjectEvents
{
public:
	template<class T>
	struct QueryObjectsArgs
	{
		const std::type_info* typeInfo;
		std::function<void(T*)> onObjectQueriedCallback;

		QueryObjectsArgs(std::function<void(T*)> onObjectQueriedCallback) : typeInfo(nullptr), onObjectQueriedCallback(onObjectQueriedCallback)
		{
		}

		void tryInvoke(SerializableObject* object)
		{
			if (typeInfo != nullptr && typeid(*object) == *typeInfo)
			{
				this->onObjectQueriedCallback(object);
			}
		}
	};

	template<class T>
	static void TriggerQueryObject(QueryObjectsArgs<T> args)
	{
		args.typeInfo = &typeid(T);

		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
			ObjectEvents::EventQueryObject,
			&args
		);
	}

	static const std::string EventQueryObject;
};
