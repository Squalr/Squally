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
	struct Properties
	{
		bool isDynamic;
		bool canRotate;

		// Used in determining pushback on objects colliding. Pushing a massless object will result in no velocity loss.
		float mass;

		Properties() : isDynamic(true), canRotate(false), mass(1.0f) { }
		Properties(bool isDynamic, bool canRotate, float mass = 1.0f) : isDynamic(isDynamic), canRotate(canRotate), mass(mass) { }
	};

	static CollisionObject* create(const cocos2d::ValueMap& properties, std::vector<cocos2d::Vec2> points, CollisionType collisionType, Properties collisionProperties);
	static CollisionObject* create(std::vector<cocos2d::Vec2> points, CollisionType collisionType, Properties collisionProperties);
	virtual ~CollisionObject();

	enum class CollisionResult
	{
		DoNothing = 0,
		CollideWithPhysics = 1
	};

	enum class Shape
	{
		Polygon,
		Segment,
		Rectangle,
		Quad,
	};

	struct CollisionData
	{
		CollisionObject* other;
		float dt;

		CollisionData() : other(nullptr), dt(0.0f) { }
		CollisionData(CollisionObject* other, float dt) : other(other), dt(dt) { }
	};

	struct CollisionEvent
	{
		std::function<CollisionResult(CollisionData)> collisionEvent;

		CollisionEvent(std::function<CollisionResult(CollisionData)> collisionEvent) : collisionEvent(collisionEvent) { }
	};

	void despawn() override;
	void warpTo(cocos2d::Vec2 location);
	void bindTo(GameObject* bindTarget);
	void unbind();
	void whenCollidesWith(std::vector<CollisionType> collisionTypes, std::function<CollisionResult(CollisionData)> onCollision);
	void whileCollidesWith(std::vector<CollisionType> collisionTypes, std::function<CollisionResult(CollisionData)> onCollision);
	void ifCollidesWith(std::vector<CollisionType> collisionTypes, std::function<CollisionResult(CollisionData)> onCollision);
	void whenStopsCollidingWith(std::vector<CollisionType> collisionTypes, std::function<CollisionResult(CollisionData)> onCollisionEnd);
	const std::vector<cocos2d::Vec2>& getPoints();
	Shape getShape();
	CollisionType getCollisionType();
	void setGravityEnabled(bool isEnabled);
	void inverseGravity();
	cocos2d::Vec2 getVelocity();
	void setVelocity(cocos2d::Vec2 velocity);
	void setVelocityX(float velocityX);
	void setVelocityY(float velocityY);
	void setHorizontalDampening(float horizontalDampening);
	void setVerticalDampening(float verticalDampening);
	std::set<CollisionObject*> getCurrentCollisions();
	bool isCollidingWith(CollisionObject* collisionObject);
	virtual void setPhysicsEnabled(bool enabled);

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
	CollisionObject(const cocos2d::ValueMap& properties, std::vector<cocos2d::Vec2> shape, CollisionType collisionType, Properties collisionProperties);

	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void onExit() override;
	void onDeveloperModeEnable(int debugLevel) override;
	void onDeveloperModeDisable() override;
	void update(float dt) override;

private:
	typedef GameObject super;
	friend class GlobalDirector;
	friend class CollisionResolver;

	void runPhysics(float dt);

	void addCollisionEvent(CollisionType collisionType, std::map<CollisionType, std::vector<CollisionEvent>>& eventMap, CollisionEvent onCollision);
	cocos2d::Vec2 getThisOrBindPosition();
	void setThisOrBindPosition(cocos2d::Vec2 position);
	Shape determineShape();

	static void ClearCollisionObjects();
	static void RegisterCollisionObject(CollisionObject* collisionObject);
	static void UnregisterCollisionObject(CollisionObject* collisionObject);

	static std::map<CollisionType, std::vector<CollisionObject*>> CollisionObjects;

	// Physics state
	cocos2d::Vec2 velocity;
	Properties collisionProperties;
	float horizontalDampening;
	float verticalDampening;
	bool physicsEnabled;
	bool gravityEnabled;
	bool gravityInversed;
	
	// Shape
	Shape shape;
	std::vector<cocos2d::Vec2> points;
	std::vector<std::tuple<cocos2d::Vec2, cocos2d::Vec2>> segments;
	cocos2d::Rect boundsRect;

	CollisionType collisionType;
	std::set<CollisionObject*>* currentCollisions;		// Will alternate between pointing to storage #1 and #2
	std::set<CollisionObject*>* previousCollisions;		// Will point to the opposite storage as the current collisions
	std::set<CollisionObject*> collisionsRed;			// Collision storage #1
	std::set<CollisionObject*> collisionsBlack;			// Collision storage #2
	GameObject* bindTarget;

	// Events
	std::set<CollisionType> collidesWithTypes;
	std::map<CollisionType, std::vector<CollisionEvent>> collisionStartEvents;
	std::map<CollisionType, std::vector<CollisionEvent>> collisionSustainEvents;
	std::map<CollisionType, std::vector<CollisionEvent>> collisionEndEvents;

	// Debug
	bool debugInfoSpawned;
	cocos2d::DrawNode* debugDrawNode;
};
