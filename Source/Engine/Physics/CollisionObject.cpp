#include "CollisionObject.h"

#include "cocos/2d/CCDrawNode.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCEventDispatcher.h"
#include "cocos/base/CCValue.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/DeveloperMode/DeveloperModeController.h"
#include "Engine/Events/CollisionEvents.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Physics/CollisionResolver.h"
#include "Engine/Utils/AlgoUtils.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/LogUtils.h"
#include "Engine/Utils/MathUtils.h"

using namespace cocos2d;

const std::string CollisionObject::MapKeyTypeCollision = "collision";
const std::string CollisionObject::MapKeyCollisionTypeNone = "none";
const std::string CollisionObject::MapKeyFriction = "friction";

std::map<CollisionType, std::vector<CollisionObject*>> CollisionObject::CollisionObjects = std::map<CollisionType, std::vector<CollisionObject*>>();

const float CollisionObject::DefaultMaxHorizontalSpeed = 600.0f;
const float CollisionObject::DefaultMaxLaunchSpeed = 720.0f;
const float CollisionObject::DefaultMaxFallSpeed = -480.0f;
const float CollisionObject::DefaultHorizontalDampening = 0.75f;
const float CollisionObject::DefaultVerticalDampening = 1.0f;
const float CollisionObject::CollisionZThreshold = 20.0f;

CollisionObject* CollisionObject::create(const ValueMap& properties, std::vector<Vec2> shape, CollisionType collisionType, bool isDynamic, bool canRotate)
{
	CollisionObject* instance = new CollisionObject(properties, shape, collisionType, isDynamic, canRotate);

	instance->autorelease();

	return instance;
}

CollisionObject* CollisionObject::create(const ValueMap& properties, std::vector<Vec2> shape, std::string collisionName, bool isDynamic, bool canRotate)
{
	CollisionObject* instance = nullptr;

	// Fire event, allowing for the game to map the deserialized collision string type (ie 'solid') to a unique integer identifier for CollisionType
	CollisionMappingEvents::requestCollisionMapKeyMapping(CollisionMappingEvents::CollisionMapRequestArgs(collisionName, [&](CollisionType collisionType)
	{
		instance = CollisionObject::create(properties, shape, collisionType, isDynamic, canRotate);
	}));

	return instance;
}

CollisionObject* CollisionObject::create(std::vector<Vec2> shape, CollisionType collisionType, bool isDynamic, bool canRotate)
{
	ValueMap valueMap = ValueMap();

	return CollisionObject::create(valueMap, shape, collisionType, isDynamic, canRotate);
}

CollisionObject* CollisionObject::create(std::vector<Vec2> shape, std::string collisionName, bool isDynamic, bool canRotate)
{
	ValueMap valueMap = ValueMap();

	return CollisionObject::create(valueMap, shape, collisionName, isDynamic, canRotate);
}

CollisionObject::CollisionObject(const ValueMap& properties, std::vector<Vec2> shape, std::string deserializedCollisionName, bool isDynamic, bool canRotate) :
	CollisionObject(properties, shape, (CollisionType)0, isDynamic, canRotate)
{
}

CollisionObject::CollisionObject(const ValueMap& properties, std::vector<Vec2> shape, CollisionType collisionType, bool isDynamic, bool canRotate) :
	super(properties)
{
	this->collisionType = collisionType;
	this->shape = shape;
	this->segments = AlgoUtils::buildSegmentsFromPoints(this->shape);
	this->boundsRect = AlgoUtils::getPolygonRect(this->shape);
	this->collidesWithTypes = std::set<CollisionType>();
	this->collisionStartEvents = std::map<CollisionType, std::vector<CollisionEvent>>();
	this->collisionSustainEvents = std::map<CollisionType, std::vector<CollisionEvent>>();
	this->collisionEndEvents = std::map<CollisionType, std::vector<CollisionEvent>>();
	this->collisionsRed = std::set<CollisionObject*>();
	this->collisionsBlack = std::set<CollisionObject*>();
	this->currentCollisions = &this->collisionsRed;
	this->previousCollisions = &this->collisionsBlack;
	this->isDynamic = isDynamic;
	this->canRotate = canRotate;
	this->physicsEnabled = true;
	this->gravityEnabled = isDynamic;
	this->gravityInversed = false;
	this->bindTarget = nullptr;
	this->debugDrawNode = nullptr;
	this->debugInfoSpawned = false;

	this->setHorizontalDampening(CollisionObject::DefaultHorizontalDampening);
	this->setVerticalDampening(CollisionObject::DefaultVerticalDampening);
}

CollisionObject::~CollisionObject()
{
}

void CollisionObject::onEnter()
{
	super::onEnter();

	CollisionObject::RegisterCollisionObject(this);

	this->currentCollisions->clear();
	this->previousCollisions->clear();

	this->scheduleUpdate();
}

void CollisionObject::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();
}

void CollisionObject::onExit()
{
	super::onExit();

	CollisionObject::UnregisterCollisionObject(this);
}

void CollisionObject::onDeveloperModeEnable(int debugLevel)
{
	super::onDeveloperModeEnable(debugLevel);

	if (this->debugDrawNode != nullptr)
	{
		this->debugDrawNode->setVisible(true);
	}

	if (!this->debugInfoSpawned && debugLevel > 0)
	{
		this->debugDrawNode = DrawNode::create();

		if (!this->shape.empty())
		{
			if (this->shape.size() == 2)
			{
				this->debugDrawNode->drawSegment(this->shape.front(), this->shape.back(), 1.0f, Color4F::RED);
			}
			else
			{
				this->debugDrawNode->drawPolygon(this->shape.data(), this->shape.size(), Color4F(1.0f, 0.0f, 0.0f, 0.4f), 1.0f, Color4F::RED);
			}
		}

		this->addChild(this->debugDrawNode);

		this->debugInfoSpawned = true;
	}
}

void CollisionObject::onDeveloperModeDisable()
{
	super::onDeveloperModeDisable();
	
	if (this->debugDrawNode != nullptr)
	{
		this->debugDrawNode->setVisible(false);
	}
}

void CollisionObject::despawn()
{
	super::despawn();

	CollisionObject::UnregisterCollisionObject(this);
}

void CollisionObject::update(float dt)
{
	super::update(dt);

	this->runPhysics(dt);
}

void CollisionObject::runPhysics(float dt)
{
	if (!this->physicsEnabled)
	{
		return;
	}

	// Apply gravity
	if (this->gravityEnabled)
	{
		const Vec2 gravity = Vec2(0.0f, -768.0f);

		this->velocity.x += gravity.x * dt;

		if (this->gravityInversed)
		{
			this->velocity.y -= gravity.y * dt;
		}
		else
		{
			this->velocity.y += gravity.y * dt;
		}
	}

	Vec2 positionUpdates = Vec2::ZERO;

	if (this->velocity != Vec2::ZERO)
	{
		// Apply dampening
		this->velocity.x *= this->horizontalDampening;
		this->velocity.y *= this->verticalDampening;

		// Enforce constraints by calling setter
		this->setVelocity(this->velocity);

		positionUpdates = Vec2(this->velocity * dt);

		this->setThisOrBindPosition(this->getThisOrBindPosition() + positionUpdates);
	}

	// Pass off current collisions to previous
	this->previousCollisions->clear();
	this->previousCollisions = this->currentCollisions;
	this->currentCollisions = this->previousCollisions == &this->collisionsBlack ? &this->collisionsRed : &this->collisionsBlack;

	for (auto collisionType : this->collidesWithTypes)
	{
		for (auto collisionObject : CollisionObject::CollisionObjects[collisionType])
		{
			CollisionResolver::resolveCollision(this, collisionObject, [=]()
			{
				// Default is colliding with physics
				CollisionResult collisionResult = CollisionResult::CollideWithPhysics;

				this->currentCollisions->insert(collisionObject);

				if (this->previousCollisions->find(collisionObject) == this->previousCollisions->end())
				{
					// Run new collision events
					for (auto event : this->collisionStartEvents[collisionType])
					{
						CollisionResult nextResult = event.collisionEvent(CollisionData(collisionObject, dt));

						collisionResult = nextResult == CollisionResult::DoNothing ? collisionResult : nextResult;
					}
				}
				else
				{
					// Run collision-sustain events
					for (auto event : this->collisionSustainEvents[collisionType])
					{
						CollisionResult nextResult = event.collisionEvent(CollisionData(collisionObject, dt));

						collisionResult = nextResult == CollisionResult::DoNothing ? collisionResult : nextResult;
					}
				}

				return collisionResult;
			});
		}
	}

	// Run collision end events
	for (auto collisionObject : *this->previousCollisions)
	{
		if (this->currentCollisions->find(collisionObject) == this->currentCollisions->end())
		{
			for (auto events : this->collisionEndEvents)
			{
				for (auto event : events.second)
				{
					event.collisionEvent(CollisionData(collisionObject, dt));
				}
			}
		}
	}
}

void CollisionObject::setPhysicsEnabled(bool enabled)
{
	this->physicsEnabled = enabled;
}

void CollisionObject::setGravityEnabled(bool isEnabled)
{
	this->gravityEnabled = isEnabled;
}

void CollisionObject::inverseGravity()
{
	this->gravityInversed = !this->gravityInversed;
}

Vec2 CollisionObject::getVelocity()
{
	return this->velocity;
}

void CollisionObject::setVelocity(Vec2 velocity)
{
	this->velocity.x = MathUtils::clamp(velocity.x, -CollisionObject::DefaultMaxHorizontalSpeed, CollisionObject::DefaultMaxHorizontalSpeed);
	this->velocity.y = MathUtils::clamp(velocity.y, CollisionObject::DefaultMaxFallSpeed, CollisionObject::DefaultMaxLaunchSpeed);
}

void CollisionObject::setVelocityX(float velocityX)
{
	this->setVelocity(Vec2(velocityX, this->getVelocity().y));
}

void CollisionObject::setVelocityY(float velocityY)
{
	this->setVelocity(Vec2(this->getVelocity().x, velocityY));
}

void CollisionObject::setHorizontalDampening(float horizontalDampening)
{
	this->horizontalDampening =  MathUtils::clamp(horizontalDampening, 0.0f, 1.0f);
}

void CollisionObject::setVerticalDampening(float verticalDampening)
{
	this->verticalDampening =  MathUtils::clamp(verticalDampening, 0.0f, 1.0f);
}
	
CollisionType CollisionObject::getCollisionType()
{
	return this->collisionType;
}

std::set<CollisionObject*> CollisionObject::getCurrentCollisions()
{
	return *this->currentCollisions;
}

bool CollisionObject::isCollidingWith(CollisionObject* collisionObject)
{
	return std::find(this->currentCollisions->begin(), this->currentCollisions->end(), collisionObject) != this->currentCollisions->end();
}

void CollisionObject::warpTo(cocos2d::Vec2 location)
{
	this->setThisOrBindPosition(location);
}

void CollisionObject::bindTo(GameObject* bindTarget)
{
	this->bindTarget = bindTarget;
}

void CollisionObject::unbind()
{
	this->bindTarget = nullptr;
}

void CollisionObject::whenCollidesWith(std::vector<CollisionType> collisionTypes, std::function<CollisionResult(CollisionData)> onCollision)
{
	for (auto collisionType : collisionTypes)
	{
		this->collidesWithTypes.insert(collisionType);
		this->collisionStartEvents[collisionType].push_back(CollisionEvent(onCollision));
	}
}

void CollisionObject::whileCollidesWith(std::vector<CollisionType> collisionTypes, std::function<CollisionResult(CollisionData)> onCollision)
{
	for (auto collisionType : collisionTypes)
	{
		this->collidesWithTypes.insert(collisionType);
		this->collisionSustainEvents[collisionType].push_back(CollisionEvent(onCollision));
	}
}

void CollisionObject::ifCollidesWith(std::vector<CollisionType> collisionTypes, std::function<CollisionResult(CollisionData)> onCollision)
{
	for (auto collisionType : collisionTypes)
	{
		this->collidesWithTypes.insert(collisionType);
		this->collisionStartEvents[collisionType].push_back(CollisionEvent(onCollision));
		this->collisionSustainEvents[collisionType].push_back(CollisionEvent(onCollision));
	}
}

void CollisionObject::whenStopsCollidingWith(std::vector<CollisionType> collisionTypes, std::function<CollisionResult(CollisionData)> onCollisionEnd)
{
	for (auto collisionType : collisionTypes)
	{
		this->collidesWithTypes.insert(collisionType);
		this->collisionEndEvents[collisionType].push_back(CollisionEvent(onCollisionEnd));
	}
}

std::vector<Vec2> CollisionObject::createCircle(float radius, int segments)
{
	std::vector<Vec2> points = std::vector<Vec2>();

	for (int index = 0; index < segments; index++)
	{

	}

	return points;
}

std::vector<Vec2> CollisionObject::createBox(Size size)
{
	return std::vector<Vec2>({
		Vec2(-size.width / 2.0f, -size.height / 2.0f),
		Vec2(-size.width / 2.0f, size.height / 2.0f),
		Vec2(size.width / 2.0f, size.height / 2.0f),
		Vec2(size.width / 2.0f, -size.height / 2.0f)
	});
}

std::vector<Vec2> CollisionObject::createCapsulePolygon(Size size, float scale, float capsuleRadius, float friction)
{
	Size newSize = size * scale;

	newSize.height = std::max(0.0f, newSize.height - capsuleRadius * 2.0f);

	std::vector<Vec2> points = std::vector<Vec2>();

	// Right side
	points.push_back(Vec2(newSize.width / 2.0f, newSize.height / 2.0f));
	points.push_back(Vec2(newSize.width / 2.0f, -newSize.height / 2.0f));

	// Bottom capsule
	points.push_back(Vec2(0.0f, -newSize.height / 2.0f - capsuleRadius));

	// Left side
	points.push_back(Vec2(-newSize.width / 2.0f, -newSize.height / 2.0f));
	points.push_back(Vec2(-newSize.width / 2.0f, newSize.height / 2.0f));

	// Top capsule
	points.push_back(Vec2(0.0f, newSize.height / 2.0f + capsuleRadius));

	return points; // PhysicsBody::createPolygon(points.data(), points.size(), PhysicsMaterial(0.5f, 0.0f, friction));
}

cocos2d::Vec2 CollisionObject::getThisOrBindPosition()
{
	if (this->bindTarget == nullptr)
	{
		return this->getPosition();
	}
	else
	{
		return this->bindTarget->getPosition();
	}
}

void CollisionObject::setThisOrBindPosition(cocos2d::Vec2 position)
{
	if (this->bindTarget == nullptr)
	{
		this->setPosition(position);
	}
	else
	{
		this->bindTarget->setPosition(position);
	}
}

void CollisionObject::ClearCollisionObjects()
{
	CollisionObject::CollisionObjects.clear();
}

void CollisionObject::RegisterCollisionObject(CollisionObject* collisionObject)
{
	if (collisionObject == nullptr)
	{
		return;
	}

	CollisionObject::CollisionObjects[collisionObject->collisionType].push_back(collisionObject);
}

void CollisionObject::UnregisterCollisionObject(CollisionObject* collisionObject)
{
	if (collisionObject == nullptr)
	{
		return;
	}

	CollisionObject::CollisionObjects[collisionObject->collisionType].erase(
		std::remove(
			CollisionObject::CollisionObjects[collisionObject->collisionType].begin(),
			CollisionObject::CollisionObjects[collisionObject->collisionType].end(),
			collisionObject
		), CollisionObject::CollisionObjects[collisionObject->collisionType].end()
	);
}
