#pragma once
#include "cocos2d.h"

#include "Engine/Physics/CollisionObject.h"

using namespace cocos2d;

class DeserializationEvents
{
public:
	static const std::string RequestCollisionMappingEvent;

	struct CollisionMapRequestArgs
	{
		CategoryName categoryName;
		CollisionObject* collisionObject;

		CollisionMapRequestArgs(CategoryName categoryName, CollisionObject* collisionObject) : categoryName(categoryName), collisionObject(collisionObject)
		{
		}
	};

	struct CollisionMapResults
	{
		CategoryGroup collisionGroup;
		std::vector<CategoryGroup>* collidesWith;

		CollisionMapResults() : collisionGroup(collisionGroup), collidesWith(collidesWith)
		{
		}
	};

	static void requestCollisionMapping(CollisionMapRequestArgs args);
};
