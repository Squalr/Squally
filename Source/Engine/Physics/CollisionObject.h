#pragma once
#include <set>
#include <string>

#include "cocos/base/ccTypes.h"

#include "Engine/Events/CollisionMappingEvents.h"
#include "Engine/Physics/EnginePhysicsTypes.h"
#include "Engine/Maps/GameObject.h"

typedef int CollisionType;

namespace cocos2d
{
	class DrawNode;
}

class CollisionObject;

enum class CollisionResult
{
	DoNothing = 0,
	CollideWithPhysics = 1
};

enum class CollisionShape
{
	Polygon,
	Segment,
	Rectangle,
	Quad,
};

struct CollisionData
{
	CollisionObject* other = nullptr;
	float dt = 0.0f;

	CollisionData() { }
	CollisionData(CollisionObject* other, float dt) : other(other), dt(dt) { }
};

struct CollisionEvent
{
	std::function<CollisionResult(CollisionData)> collisionEvent;

	CollisionEvent(std::function<CollisionResult(CollisionData)> collisionEvent) : collisionEvent(collisionEvent) { }
};

class CollisionObject : public GameObject
{
public:
	struct Properties
	{
		bool isDynamic = false;
		bool canRotate = false;

		// Used in determining pushback on objects colliding. Pushing a massless object will result in no velocity loss.
		float mass = 0.0f;
		
		// Used in mitigating corrections applied in collisions. Helps smooth out otherwise rough collisions.
		float softness = 0.0f;

		Properties() : isDynamic(true), canRotate(false), mass(1.0f), softness(1.0f) { }
		Properties(bool isDynamic, bool canRotate, float mass = 1.0f, float softness = 1.0f) : isDynamic(isDynamic), canRotate(canRotate), mass(mass), softness(softness) { }
	};

	static CollisionObject* create(const cocos2d::ValueMap& properties, std::vector<cocos2d::Vec2> points, CollisionType collisionType, Properties collisionProperties, cocos2d::Color4F debugColor = cocos2d::Color4F::RED);
	static CollisionObject* create(std::vector<cocos2d::Vec2> points, CollisionType collisionType, Properties collisionProperties, cocos2d::Color4F debugColor = cocos2d::Color4F::RED);
	virtual ~CollisionObject();

	void warpTo(cocos2d::Vec3 location);
	void bindTo(GameObject* bindTarget);
	void unbind();
	void whenCollidesWith(std::vector<CollisionType> collisionTypes, std::function<CollisionResult(CollisionData)> onCollision);
	void whileCollidesWith(std::vector<CollisionType> collisionTypes, std::function<CollisionResult(CollisionData)> onCollision);
	void ifCollidesWith(std::vector<CollisionType> collisionTypes, std::function<CollisionResult(CollisionData)> onCollision);
	void whenStopsCollidingWith(std::vector<CollisionType> collisionTypes, std::function<CollisionResult(CollisionData)> onCollisionEnd);
	const std::vector<cocos2d::Vec2>& getPoints();
	void setPoints(std::vector<cocos2d::Vec2> points);
	CollisionShape getShape();
	CollisionType getCollisionType();
	std::vector<CollisionType> getCollisionTypes();
	bool hasCollisionType(CollisionType collisionType);
	bool hasCollisionWith(CollisionObject* object);
	bool isCollidingWithSingleGroup();
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
	float getHorizontalDampening();
	float getVerticalDampening();
	const std::set<CollisionObject*>& getCurrentCollisions();
	bool hasCollisions();
	bool isCollidingWith(CollisionObject* collisionObject);
	bool wasCollidingWith(CollisionObject* collisionObject);
	bool isCollidingWithType(int collisionType);
	bool wasCollidingWithType(int collisionType);
	void setCollisionDepth(float collisionDepth);
	void setGravityFlagEnabled(bool isEnabled, int flagIndex = (int)EngineGravityFlags::Default);
	bool getGravityFlagEnabled(int flagIndex = (int)EngineGravityFlags::Default);
	bool getGravityEnabled();
	void setPhysicsFlagEnabled(bool isEnabled, int flagIndex = (int)EnginePhysicsFlags::Default);
	bool getPhysicsFlagEnabled(int flagIndex = (int)EnginePhysicsFlags::Default);
	bool getPhysicsEnabled();
	void setCollisionFlagEnabled(bool isEnabled, int flagIndex = (int)EngineCollisionFlags::Default);
	bool getCollisionFlagEnabled(int flagIndex = (int)EngineCollisionFlags::Default);
	bool getCollisionEnabled();
	unsigned int getUniverseId();
	cocos2d::Vec2 getCachedWorldCoords();
	cocos2d::Vec3 getCachedWorldCoords3D();
	const std::vector<std::tuple<cocos2d::Vec2, cocos2d::Vec2>>& getSegmentsRotated();

	static std::vector<cocos2d::Vec2> createCircle(float radius, int segments = 24);
	static std::vector<cocos2d::Vec2> createSegmentX(float width);
	static std::vector<cocos2d::Vec2> createSegmentY(float height);
	static std::vector<cocos2d::Vec2> createBox(cocos2d::CSize size);
	static std::vector<cocos2d::Vec2> createCapsulePolygon(cocos2d::CSize size, float capsuleRadius = 8.0f);

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
	CollisionShape determineShape();
	void computeDepth(bool force = false);
	void computeWorldCoords(bool force = false);
	void propagateRotation(bool force = false);

	void drawDebugShapes();
	void drawDebugConnectors();

	static void ClearCollisionObjects();
	static void RegisterCollisionObject(CollisionObject* collisionObject);
	static void UnregisterCollisionObject(CollisionObject* collisionObject);

	static std::map<CollisionType, std::vector<CollisionObject*>> CollisionObjects;

	// Physics state
	cocos2d::Vec2 gravity = cocos2d::Vec2::ZERO;
	cocos2d::Vec2 velocity = cocos2d::Vec2::ZERO;
	cocos2d::Vec2 acceleration = cocos2d::Vec2::ZERO;
	Properties collisionProperties;
	float horizontalDampening = 0.0f;
	float verticalDampening = 0.0f;
	float collisionDepth = 0.0f;

	// These are set as flags such that multiple disabled sources can be set (ie disabled from death, mounting, etc).
	// If any flag is set, the corresponding component is considered to be disabled
	int physicsDisabledFlags = 0;
	int collisionDisabledFlags = 0;
	int gravityDisabledFlags = 0;

	unsigned int universeId = 0;
	
	// Shape
	CollisionShape shape = CollisionShape::Polygon;
	std::vector<cocos2d::Vec2> points;
	std::vector<cocos2d::Vec2> pointsRotated;
	std::vector<std::tuple<cocos2d::Vec2, cocos2d::Vec2>> segments;
	std::vector<std::tuple<cocos2d::Vec2, cocos2d::Vec2>> segmentsRotated;
	cocos2d::CRect boundsRect;

	CollisionType collisionType = 0;
	std::vector<CollisionType> collisionTypes;
	std::set<CollisionObject*>* currentCollisions;		// Will alternate between pointing to storage #1 and #2
	std::set<CollisionObject*>* previousCollisions;		// Will point to the opposite storage as the current collisions
	std::set<CollisionObject*> collisionsRed;			// Collision storage #1
	std::set<CollisionObject*> collisionsBlack;			// Collision storage #2
	GameObject* bindTarget = nullptr;

	// Events
	std::set<CollisionType> collidesWithTypes;
	std::map<CollisionType, std::vector<CollisionEvent>> collisionStartEvents;
	std::map<CollisionType, std::vector<CollisionEvent>> collisionSustainEvents;
	std::map<CollisionType, std::vector<CollisionEvent>> collisionEndEvents;

	// Cache
	float cachedRotation = 0.0f;
	cocos2d::Vec2 cachedWorldCoords;
	cocos2d::Vec3 cachedWorldCoords3D;
	unsigned int cachedTick = 0;
	unsigned int cachedTickDepth = 0;

	// Debug
	cocos2d::Color4F debugColor;
	bool debugInfoSpawned = false;
	cocos2d::Node* debugDrawNode = nullptr;
	cocos2d::DrawNode* debugDrawNodeConnectors = nullptr;
};
