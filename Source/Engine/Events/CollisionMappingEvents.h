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
	static const std::string RequestAllowedCollisionMappingEvent;

	struct CollisionMapRequestArgs
	{
		std::string deserializedCollisionName;
		CollisionObject* collisionObject;

		CollisionMapRequestArgs(std::string deserializedCollisionName, CollisionObject* collisionObject) :
			deserializedCollisionName(deserializedCollisionName), collisionObject(collisionObject)
		{
		}
	};

	struct AllowedCollisionsRequestArgs
	{
		int collisionType;
		CollisionObject* collisionObject;

		AllowedCollisionsRequestArgs(int collisionType, CollisionObject* collisionObject) :
			collisionType(collisionType), collisionObject(collisionObject)
		{
		}
	};

	static void requestCollisionMapKeyMapping(CollisionMapRequestArgs args);
	static void requestAllowedCollisionMapping(AllowedCollisionsRequestArgs args);
};
