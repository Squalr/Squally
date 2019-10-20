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
	static CollisionObject* create(const cocos2d::ValueMap& properties, cocos2d::PhysicsBody* physicsBody, CollisionType collisionType, bool isDynamic, bool canRotate);
	static CollisionObject* create(const cocos2d::ValueMap& properties, cocos2d::PhysicsBody* physicsBody, std::string collisionName, bool isDynamic, bool canRotate);
	static CollisionObject* create(cocos2d::PhysicsBody* physicsBody, CollisionType collisionType, bool isDynamic, bool canRotate);
	static CollisionObject* create(cocos2d::PhysicsBody* physicsBody, std::string collisionName, bool isDynamic, bool canRotate);
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

	struct CollisionEvent
	{
		std::function<CollisionResult(CollisionData)> collisionEvent;

		CollisionEvent(std::function<CollisionResult(CollisionData)> collisionEvent) : collisionEvent(collisionEvent) { }
	};

	void buildInverseCollisionMap();
	void addPhysicsShape(cocos2d::PhysicsShape* shape);
	void bindTo(cocos2d::Node* bindTarget);
	void unbind();
	void whenCollidesWith(std::vector<CollisionType> collisionTypes, std::function<CollisionResult(CollisionData)> onCollision);
	void whenStopsCollidingWith(std::vector<CollisionType> collisionTypes, std::function<CollisionResult(CollisionData)> onCollisionEnd);
	void setCollisionType(CollisionType collisionType);
	CollisionType getCollisionType();
	void setGravityEnabled(bool isEnabled);
	void inverseGravity();
	void setPosition(const cocos2d::Vec2& position) override;
	cocos2d::Vec2 getVelocity();
	void setVelocity(cocos2d::Vec2 velocity);
	void setVelocityX(float velocityX);
	void setVelocityY(float velocityY);
	void setAngularVelocity(float angularVelocity);
	void setHorizontalDampening(float horizontalDampening);
	void setVerticalDampening(float verticalDampening);
	std::vector<CollisionObject*> getCurrentCollisions();
	bool isCollidingWith(CollisionObject* collisionObject);
	virtual void setPhysicsEnabled(bool enabled);
	virtual void setContactUpdateCallback(std::function<void(const std::vector<CollisionObject*>& currentCollisions, float dt)> contactUpdateCallback);
	void setDebugPositionSetCallback(std::function<void()> onDebugPositionSet);
	static cocos2d::PhysicsBody* createCapsulePolygon(cocos2d::Size size, float scale, float capsuleRadius);

	static const std::string MapKeyTypeCollision;
	static const std::string MapKeyCollisionTypeNone;
	static const float DefaultMaxHorizontalSpeed;
	static const float DefaultMaxLaunchSpeed;
	static const float DefaultMaxFallSpeed;
	static const float DefaultHorizontalDampening;
	static const float DefaultVerticalDampening;
	static const float CollisionZThreshold;

protected:
	CollisionObject(const cocos2d::ValueMap& properties, cocos2d::PhysicsBody* initPhysicsBody,
		std::string deserializedCollisionName, bool isDynamic, bool canRotate);
	CollisionObject(const cocos2d::ValueMap& properties, cocos2d::PhysicsBody* initPhysicsBody,
		CollisionType collisionType, bool isDynamic, bool canRotate);
	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void initializeListeners() override;
	void update(float dt) override;
	void visit(cocos2d::Renderer *renderer, const cocos2d::Mat4& parentTransform, uint32_t parentFlags) override;

private:
	typedef HackableObject super;
	// We need to let the dispatcher call our events directly when it determines that this object was involved in a collision
	friend class CollisionEventDispatcher;

	void addCollisionEvent(CollisionType collisionType, std::map<CollisionType, std::vector<CollisionEvent>>& eventMap, CollisionEvent onCollision);
	bool onContactBegin(cocos2d::PhysicsContact& contact);
	bool onContactUpdate(cocos2d::PhysicsContact& contact);
	bool onContactEnd(cocos2d::PhysicsContact& contact);
	bool runContactEvents(cocos2d::PhysicsContact& contact, std::map<CollisionType, std::vector<CollisionEvent>>& eventMap, CollisionResult defaultResult, const CollisionData& collisionData);
	CollisionData constructCollisionData(cocos2d::PhysicsContact& contact);
	void updateBinds();
	bool isWithinZThreshold(cocos2d::PhysicsContact& contact, const CollisionData& collisionData);

	std::map<CollisionType, std::vector<CollisionEvent>> collisionEvents;
	std::map<CollisionType, std::vector<CollisionEvent>> collisionEndEvents;
	cocos2d::PhysicsBody* physicsBody;
	cocos2d::Node* bindTarget;
	float horizontalDampening;
	float verticalDampening;
	std::function<void(const std::vector<CollisionObject*>& currentCollisions, float dt)> contactUpdateCallback;
	std::vector<CollisionObject*> currentCollisions;
	static std::map<int, int> InverseCollisionMap;
	bool gravityEnabled;
	bool gravityInversed;
	std::function<void()> onDebugPositionSet;
};
