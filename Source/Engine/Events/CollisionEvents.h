#pragma once
#include <functional>
#include <string>

class CollisionObject;

class CollisionEvents
{
public:
	static const std::string EventQueryCollisionObjectPrefix;
		
	struct QueryCollisionObjectsArgs
	{
		std::function<void(CollisionObject*)> onObjectQueriedCallback;
		int bitmask;
		
		QueryCollisionObjectsArgs(std::function<void(CollisionObject*)> onObjectQueriedCallback, int bitmask) : onObjectQueriedCallback(onObjectQueriedCallback), bitmask(bitmask)
		{
		}

		void invoke(CollisionObject* object)
		{
			if (onObjectQueriedCallback != nullptr)
			{
				this->onObjectQueriedCallback(object);
			}
		}
	};

	static void QueryCollisionObjects(QueryCollisionObjectsArgs args);
};
