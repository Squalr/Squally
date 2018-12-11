#pragma once
#include <string>

#include "cocos/math/Vec2.h"

#include "Engine/Hackables/HackableObject.h"

typedef std::string DeserializedCollisionName;
typedef int CollisionType;

namespace cocos2d
{
	class PhysicsBody;
	class PhysicsContact;
	class Value;
	typedef std::map<std::string, Value> ValueMap;
}

class CollisionObject : public HackableObject
{
public:
	static const std::string RequestCollisionMappingEvent;

	struct CollisionMapRequestArgs
	{
		DeserializedCollisionName deserializedCollisionName;
		CollisionObject* collisionObject;

		CollisionMapRequestArgs(DeserializedCollisionName deserializedCollisionName, CollisionObject* collisionObject) :
			deserializedCollisionName(deserializedCollisionName), collisionObject(collisionObject)
		{
		}
	};

	static void requestCollisionMapping(CollisionMapRequestArgs args);

	CollisionObject(cocos2d::ValueMap* initProperties, cocos2d::PhysicsBody* initPhysicsBody,
		DeserializedCollisionName deserializedCollisionName, bool isDynamic, bool canRotate);
	CollisionObject(cocos2d::ValueMap* initProperties, cocos2d::PhysicsBody* initPhysicsBody,
		CollisionType collisionType, bool isDynamic, bool canRotate);
	virtual ~CollisionObject();

	void setCollisionType(CollisionType collisionType);

	CollisionType getCollisionType();
	cocos2d::Vec2 getVelocity();
	void setVelocity(cocos2d::Vec2 velocity);

	virtual void setPhysicsEnabled(bool enabled);

	static std::string MapKeyTypeCollision;

protected:
	enum class CollisionResult
	{
		DoNothing,
		CollideWithPhysics
	};

	enum class CollisionDirection
	{
		None,
		Left,
		Right,
		Up,
		Down,
		StepLeft,
		StepRight,
	};

	struct CollisionData
	{
		CollisionObject* other;
		cocos2d::Vec2 normal;
		CollisionDirection direction;
		cocos2d::Vec2 points[4];
		int pointCount;

		CollisionData(CollisionObject* other, cocos2d::Vec2 normal, CollisionDirection direction,
				const cocos2d::Vec2* points, int pointCount) :
			other(other), normal(normal), direction(direction), pointCount(pointCount)
		{
		}
	};

	void whenCollidesWith(CollisionType collisionType, std::function<CollisionResult(CollisionData)> onCollision);
	void whenCollidesWith(std::vector<CollisionType> collisionTypes, std::function<CollisionResult(CollisionData)> onCollision);
	void whenStopsCollidingWith(CollisionType collisionType, std::function<CollisionResult(CollisionData)> onCollisionEnd);
	void whenStopsCollidingWith(std::vector<CollisionType> collisionTypes, std::function<CollisionResult(CollisionData)> onCollisionEnd);

	void onEnter() override;
	void initializeListeners() override;
	void update(float dt) override;

private:
	bool onContactBegin(cocos2d::PhysicsContact& contact);
	bool onContactUpdate(cocos2d::PhysicsContact& contact);
	bool onContactEnd(cocos2d::PhysicsContact& contact);

	CollisionData constructCollisionData(cocos2d::PhysicsContact& contact);

	std::map<CollisionType, std::vector<std::function<CollisionResult(CollisionData)>>> collisionEvents;
	std::map<CollisionType, std::vector<std::function<CollisionResult(CollisionData)>>> collisionEndEvents;
	cocos2d::PhysicsBody* physicsBody;

	bool physicsEnabled;
};
