#pragma once

#include <functional>
#include <string>

class CollisionMappingEvents
{
public:
	static const std::string RequestCollisionMapKeyMappingEvent;

	struct CollisionMapRequestArgs
	{
		std::string deserializedCollisionName;
		std::function<void(int collisionType)> callback;

		CollisionMapRequestArgs(std::string deserializedCollisionName, std::function<void(int collisionType)> callback) :
			deserializedCollisionName(deserializedCollisionName), callback(callback)
		{
		}
	};

	static void requestCollisionMapKeyMapping(CollisionMapRequestArgs args);
};
