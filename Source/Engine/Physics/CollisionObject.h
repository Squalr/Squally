#pragma once
#include <string>

#include "cocos/math/Vec2.h"

#include "Engine/Events/CollisionMappingEvents.h"
#include "Engine/Hackables/HackableObject.h"

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
	static CollisionObject* create(cocos2d::PhysicsBody* physicsBody, CollisionType collisionType, bool isDynamic, bool canRotate);

	CollisionObject(cocos2d::ValueMap* initProperties, cocos2d::PhysicsBody* initPhysicsBody,
		std::string deserializedCollisionName, bool isDynamic, bool canRotate);
	CollisionObject(cocos2d::ValueMap* initProperties, cocos2d::PhysicsBody* initPhysicsBody,
		CollisionType collisionType, bool isDynamic, bool canRotate);
	virtual ~CollisionObject();

	enum class CollisionResult
	{
		DoNothing,
		CollideWithPhysics
	};

	struct CollisionData
	{
		CollisionObject* other;

		CollisionData(CollisionObject* other) : other(other)
		{
		}
	};

	void addPhysicsShape(cocos2d::PhysicsShape* shape);
	void whenCollidesWith(std::vector<CollisionType> collisionTypes, std::function<CollisionResult(CollisionData)> onCollision);
	void whenStopsCollidingWith(std::vector<CollisionType> collisionTypes, std::function<CollisionResult(CollisionData)> onCollisionEnd);

	void setCollisionType(CollisionType collisionType);
	CollisionType getCollisionType();
	cocos2d::Vec2 getVelocity();
	void setVelocity(cocos2d::Vec2 velocity);
	virtual void setPhysicsEnabled(bool enabled);

	static const std::string MapKeyTypeCollision;

protected:

	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void initializeListeners() override;
	void update(float dt) override;

private:
	// We need to let the dispatcher call our events directly when it determines that this object was involved in a collision
	friend class CollisionEventDispatcher;

	void addCollisionEvent(CollisionType collisionType, std::map<CollisionType, std::vector<std::function<CollisionResult(CollisionData)>>>& eventMap, std::function<CollisionResult(CollisionData)> onCollision);
	bool onContactBegin(cocos2d::PhysicsContact& contact);
	bool onContactUpdate(cocos2d::PhysicsContact& contact);
	bool onContactEnd(cocos2d::PhysicsContact& contact);
	bool runContactEvents(cocos2d::PhysicsContact& contact, std::map<CollisionType, std::vector<std::function<CollisionResult(CollisionData)>>>& eventMap, CollisionResult defaultResult);
	CollisionData constructCollisionData(cocos2d::PhysicsContact& contact);

	std::map<CollisionType, std::vector<std::function<CollisionResult(CollisionData)>>> collisionEvents;
	std::map<CollisionType, std::vector<std::function<CollisionResult(CollisionData)>>> collisionEndEvents;
	cocos2d::PhysicsBody* physicsBody;

	static std::map<int, int> InverseCollisionMap;
	bool physicsEnabled;
};
