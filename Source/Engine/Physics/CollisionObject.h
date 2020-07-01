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
		
		// Used in mitigating corrections applied in collisions. Helps smooth out otherwise rough collisions.
		float softness;

		Properties() : isDynamic(true), canRotate(false), mass(1.0f), softness(1.0f) { }
		Properties(bool isDynamic, bool canRotate, float mass = 1.0f, float softness = 1.0f) : isDynamic(isDynamic), canRotate(canRotate), mass(mass), softness(softness) { }
	};

	static CollisionObject* create(const cocos2d::ValueMap& properties, std::vector<cocos2d::Vec2> points, CollisionType collisionType, Properties collisionProperties, cocos2d::Color4F debugColor = cocos2d::Color4F::RED);
	static CollisionObject* create(std::vector<cocos2d::Vec2> points, CollisionType collisionType, Properties collisionProperties, cocos2d::Color4F debugColor = cocos2d::Color4F::RED);
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

	void warpTo(cocos2d::Vec3 location);
	void bindTo(GameObject* bindTarget);
	void unbind();
	void whenCollidesWith(std::vector<CollisionType> collisionTypes, std::function<CollisionResult(CollisionData)> onCollision);
	void whileCollidesWith(std::vector<CollisionType> collisionTypes, std::function<CollisionResult(CollisionData)> onCollision);
	void ifCollidesWith(std::vector<CollisionType> collisionTypes, std::function<CollisionResult(CollisionData)> onCollision);
	void whenStopsCollidingWith(std::vector<CollisionType> collisionTypes, std::function<CollisionResult(CollisionData)> onCollisionEnd);
	const std::vector<cocos2d::Vec2>& getPoints();
	void setPoints(std::vector<cocos2d::Vec2> points);
	Shape getShape();
	CollisionType getCollisionType();
	std::vector<CollisionType> getCollisionTypes();
	bool hasCollisionType(CollisionType collisionType);
	bool hasCollisionWith(CollisionObject* object);
	void setGravityEnabled(bool isEnabled);
	cocos2d::Vec2 getVelocity();
	cocos2d::Vec2 getAcceleration();
	void setVelocity(cocos2d::Vec2 velocity);
	void setVelocityX(float velocityX);
	void setVelocityY(float velocityY);
	void setGravity(cocos2d::Vec2 acceleration);
	cocos2d::Vec2 getGravity();
	void setAcceleration(cocos2d::Vec2 acceleration);
	void setAccelerationX(float accelerationX);
	void setAccelerationY(float accelerationY);
	void setHorizontalDampening(float horizontalDampening);
	void setVerticalDampening(float verticalDampening);
	const std::set<CollisionObject*>& getCurrentCollisions();
	bool isCollidingWith(CollisionObject* collisionObject);
	bool wasCollidingWith(CollisionObject* collisionObject);
	bool isCollidingWithType(int collisionType);
	bool wasCollidingWithType(int collisionType);
	void setCollisionDepth(float collisionDepth);
	virtual void setPhysicsEnabled(bool enabled);
	unsigned int getUniverseId();

	static std::vector<cocos2d::Vec2> createCircle(float radius, int segments = 24);
	static std::vector<cocos2d::Vec2> createBox(cocos2d::Size size);
	static std::vector<cocos2d::Vec2> createCapsulePolygon(cocos2d::Size size, float capsuleRadius = 8.0f);

	static const std::string MapKeyTypeCollision;
	static const std::string MapKeyCollisionTypeNone;
	static const std::string MapKeyFriction;
	static const float DefaultGravity;
	static const float DefaultMaxHorizontalSpeed;
	static const float DefaultMaxLaunchSpeed;
	static const float DefaultMaxFallSpeed;
	static const float DefaultHorizontalDampening;
	static const float DefaultVerticalDampening;
	static const float CollisionZThreshold;
	static unsigned int UniverseId;
	static unsigned int AlternateUniverseCounter;

protected:
	CollisionObject(const cocos2d::ValueMap& properties, std::vector<cocos2d::Vec2> shape, CollisionType collisionType, Properties collisionProperties, cocos2d::Color4F debugColor);

	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void onExit() override;
	void onDeveloperModeEnable(int debugLevel) override;
	void onDeveloperModeDisable() override;
	void update(float dt) override;
	void onDespawn() override;

private:
	typedef GameObject super;
	friend class GlobalDirector;
	friend class CollisionResolver;

	void runPhysics(float dt);

	void addCollisionEvent(CollisionType collisionType, std::map<CollisionType, std::vector<CollisionEvent>>& eventMap, CollisionEvent onCollision);
	cocos2d::Vec3 getThisOrBindPosition();
	void setThisOrBindPosition(cocos2d::Vec3 position);
	Shape determineShape();
	void computeWorldCoords(bool force = false);
	void propagateRotation(bool force = false);

	void drawDebugShapes();
	void drawDebugConnectors();

	static void ClearCollisionObjects();
	static void RegisterCollisionObject(CollisionObject* collisionObject);
	static void UnregisterCollisionObject(CollisionObject* collisionObject);

	static std::map<CollisionType, std::vector<CollisionObject*>> CollisionObjects;

	// Physics state
	cocos2d::Vec2 gravity;
	cocos2d::Vec2 velocity;
	cocos2d::Vec2 acceleration;
	Properties collisionProperties;
	float horizontalDampening;
	float verticalDampening;
	float collisionDepth;
	bool physicsEnabled;
	bool gravityEnabled;
	unsigned int universeId;
	
	// Shape
	Shape shape;
	std::vector<cocos2d::Vec2> points;
	std::vector<cocos2d::Vec2> pointsRotated;
	std::vector<std::tuple<cocos2d::Vec2, cocos2d::Vec2>> segments;
	std::vector<std::tuple<cocos2d::Vec2, cocos2d::Vec2>> segmentsRotated;
	cocos2d::Rect boundsRect;

	CollisionType collisionType;
	std::vector<CollisionType> collisionTypes;
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

	// Cache
	float cachedRotation;
	cocos2d::Vec2 cachedWorldCoords;
	cocos2d::Vec3 cachedWorldCoords3D;
	unsigned int cachedTick;

	// Debug
	cocos2d::Color4F debugColor;
	bool debugInfoSpawned;
	cocos2d::Node* debugDrawNode;
	cocos2d::DrawNode* debugDrawNodeConnectors;
};
