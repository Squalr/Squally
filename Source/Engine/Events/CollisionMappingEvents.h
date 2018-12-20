#pragma once
#include "cocos/base/CCValue.h"
#include "cocos/math/CCGeometry.h"

class CollisionObject;

namespace cocos2d
{
	class TMXObjectGroup;
}

class CollisionMappingEvents
{
public:
	static const std::string RequestCollisionMapKeyMappingEvent;

	struct CollisionMapRequestArgs
	{
		std::string deserializedCollisionName;
		CollisionObject* collisionObject;

		CollisionMapRequestArgs(std::string deserializedCollisionName, CollisionObject* collisionObject) :
			deserializedCollisionName(deserializedCollisionName), collisionObject(collisionObject)
		{
		}
	};

	static void requestCollisionMapKeyMapping(CollisionMapRequestArgs args);
};
