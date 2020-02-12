#pragma once
#include <set>
#include <string>

#include "cocos/math/Vec2.h"

#include "Engine/Events/CollisionMappingEvents.h"
#include "Engine/Maps/GameObject.h"

typedef int CollisionType;

namespace cocos2d
{
	class DrawNode;
	class Value;
	typedef std::map<std::string, Value> ValueMap;
}

class CollisionObject : public GameObject
{
public:
	static CollisionObject* create(const cocos2d::ValueMap& properties, std::vector<cocos2d::Vec2> shape, CollisionType collisionType, bool isDynamic, bool canRotate);
	static CollisionObject* create(const cocos2d::ValueMap& properties, std::vector<cocos2d::Vec2> shape, std::string collisionName, bool isDynamic, bool canRotate);
	static CollisionObject* create(std::vector<cocos2d::Vec2> shape, CollisionType collisionType, bool isDynamic, bool canRotate);
	static CollisionObject* create(std::vector<cocos2d::Vec2> shape, std::string collisionName, bool isDynamic, bool canRotate);
	virtual ~CollisionObject();

	enum class CollisionResult
	{
		DoNothing = 0,
		CollideWithPhysics = 1
	};

	struct CollisionData
	{
		CollisionObject* other;

		CollisionData() : other(nullptr) { }
		CollisionData(CollisionObject* other) : other(other) { }
	};

	struct CollisionEvent
	{
		std::function<CollisionResult(CollisionData)> collisionEvent;

		CollisionEvent(std::function<CollisionResult(CollisionData)> collisionEvent) : collisionEvent(collisionEvent) { }
	};

	void despawn() override;
	void bindTo(GameObject* bindTarget);
	void unbind();
	void whenCollidesWith(std::vector<CollisionType> collisionTypes, std::function<CollisionResult(CollisionData)> onCollision);
	void whenStopsCollidingWith(std::vector<CollisionType> collisionTypes, std::function<CollisionResult(CollisionData)> onCollisionEnd);
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

	static std::vector<cocos2d::Vec2> createCircle(float radius, int segments = 24);
	static std::vector<cocos2d::Vec2> createBox(cocos2d::Size size);
	static std::vector<cocos2d::Vec2> createCapsulePolygon(cocos2d::Size size, float scale = 1.0f, float capsuleRadius = 8.0f, float friction = 0.5f);

	static const std::string MapKeyTypeCollision;
	static const std::string MapKeyCollisionTypeNone;
	static const std::string MapKeyFriction;
	static const float DefaultMaxHorizontalSpeed;
	static const float DefaultMaxLaunchSpeed;
	static const float DefaultMaxFallSpeed;
	static const float DefaultHorizontalDampening;
	static const float DefaultVerticalDampening;
	static const float CollisionZThreshold;

protected:
	CollisionObject(const cocos2d::ValueMap& properties, std::vector<cocos2d::Vec2> shape,
		std::string deserializedCollisionName, bool isDynamic, bool canRotate);
	CollisionObject(const cocos2d::ValueMap& properties, std::vector<cocos2d::Vec2> shape,
		CollisionType collisionType, bool isDynamic, bool canRotate);

	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void onExit() override;
	void initializeListeners() override;
	void onDeveloperModeEnable(int debugLevel) override;
	void onDeveloperModeDisable() override;
	void update(float dt) override;

private:
	typedef GameObject super;
	friend class GlobalDirector;

	void runPhysics(float dt);

	void addCollisionEvent(CollisionType collisionType, std::map<CollisionType, std::vector<CollisionEvent>>& eventMap, CollisionEvent onCollision);
	// bool onContactBegin(cocos2d::PhysicsContact& contact);
	// bool onContactUpdate(cocos2d::PhysicsContact& contact);
	// bool onContactRetry(CollisionData& collisionData);
	// bool onContactEnd(cocos2d::PhysicsContact& contact);
	bool runContactEvents(std::map<CollisionType, std::vector<CollisionEvent>>& eventMap, CollisionResult defaultResult, const CollisionData& collisionData);
	// CollisionData constructCollisionData(cocos2d::PhysicsContact& contact);
	bool collidesWith(CollisionObject* collisionObject);
	bool isWithinZThreshold(const CollisionData& collisionData);

	static void ClearCollisionObjects();
	static void RegisterCollisionObject(CollisionObject* collisionObject);
	static void UnregisterCollisionObject(CollisionObject* collisionObject);

	static std::map<CollisionType, std::vector<CollisionObject*>> CollisionObjects;

	// Physics state
	cocos2d::Vec2 velocity;
	float horizontalDampening;
	float verticalDampening;

	std::map<CollisionType, std::vector<CollisionEvent>> collisionEvents;
	std::map<CollisionType, std::vector<CollisionEvent>> collisionEndEvents;
	std::function<void(const std::vector<CollisionObject*>& currentCollisions, float dt)> contactUpdateCallback;
	std::map<CollisionObject*, CollisionData> passThroughCandidates;
	std::map<CollisionObject*, CollisionData> passThroughCandidatesIter;
	std::vector<CollisionObject*> currentCollisions;
	std::vector<cocos2d::Vec2> shape;
	cocos2d::Rect boundsRect;
	CollisionType collisionType;
	GameObject* bindTarget;
	bool gravityEnabled;
	bool gravityInversed;
	bool debugInfoSpawned;
	cocos2d::DrawNode* debugDrawNode;
};
