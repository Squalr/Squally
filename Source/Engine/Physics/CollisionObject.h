#pragma once
#include <set>
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

	CollisionObject(const cocos2d::ValueMap& initProperties, cocos2d::PhysicsBody* initPhysicsBody,
		std::string deserializedCollisionName, bool isDynamic, bool canRotate);
	CollisionObject(const cocos2d::ValueMap& initProperties, cocos2d::PhysicsBody* initPhysicsBody,
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
	void bindTo(cocos2d::Node* bindTarget);
	void forceBindTo(cocos2d::Node* bindTarget, float forceBounceFactor);
	void whenCollidesWith(std::vector<CollisionType> collisionTypes, std::function<CollisionResult(CollisionData)> onCollision);
	void whenStopsCollidingWith(std::vector<CollisionType> collisionTypes, std::function<CollisionResult(CollisionData)> onCollisionEnd);
	void setCollisionType(CollisionType collisionType);
	CollisionType getCollisionType();
	void setGravityEnabled(bool isEnabled);
	void setPosition(const cocos2d::Vec2& position) override;
	cocos2d::Vec2 getVelocity();
	void setVelocity(cocos2d::Vec2 velocity);
	void setHorizontalDampening(float horizontalDampening);
	void setVerticalDampening(float verticalDampening);
	std::set<CollisionObject*> getCurrentCollisions();
	virtual void setPhysicsEnabled(bool enabled);
	virtual void setContactUpdateCallback(std::function<void(std::set<CollisionObject*>* currentCollisions, float dt)> contactUpdateCallback);

	static const std::string MapKeyTypeCollision;
	static const float DefaultMaxHorizontalSpeed;
	static const float DefaultMaxLaunchSpeed;
	static const float DefaultMaxFallSpeed;
	static const float DefaultHorizontalDampening;
	static const float DefaultVerticalDampening;

protected:
	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void initializeListeners() override;
	void update(float dt) override;
	void visit(cocos2d::Renderer *renderer, const cocos2d::Mat4& parentTransform, uint32_t parentFlags) override;

private:
	typedef HackableObject super;
	// We need to let the dispatcher call our events directly when it determines that this object was involved in a collision
	friend class CollisionEventDispatcher;

	void addCollisionEvent(CollisionType collisionType, std::map<CollisionType, std::vector<std::function<CollisionResult(CollisionData)>>>& eventMap, std::function<CollisionResult(CollisionData)> onCollision);
	bool onContactBegin(cocos2d::PhysicsContact& contact);
	bool onContactUpdate(cocos2d::PhysicsContact& contact);
	bool onContactEnd(cocos2d::PhysicsContact& contact);
	bool runContactEvents(cocos2d::PhysicsContact& contact, std::map<CollisionType, std::vector<std::function<CollisionResult(CollisionData)>>>& eventMap, CollisionResult defaultResult, const CollisionData& collisionData);
	CollisionData constructCollisionData(cocos2d::PhysicsContact& contact);
	void updateBinds();

	std::map<CollisionType, std::vector<std::function<CollisionResult(CollisionData)>>> collisionEvents;
	std::map<CollisionType, std::vector<std::function<CollisionResult(CollisionData)>>> collisionEndEvents;
	cocos2d::PhysicsBody* physicsBody;
	cocos2d::Node* bindTarget;
	cocos2d::Node* forceBindTarget;
	float horizontalDampening;
	float verticalDampening;
	float forceBounceFactor;
	std::function<void(std::set<CollisionObject*>* currentCollisions, float dt)> contactUpdateCallback;
	std::set<CollisionObject*> currentCollisions;
	static std::map<int, int> InverseCollisionMap;
	bool physicsEnabled;
};
