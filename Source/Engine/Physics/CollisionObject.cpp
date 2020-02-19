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

const float CollisionObject::DefaultGravity = -768.0f;
const float CollisionObject::DefaultMaxHorizontalSpeed = 600.0f;
const float CollisionObject::DefaultMaxLaunchSpeed = 720.0f;
const float CollisionObject::DefaultMaxFallSpeed = -480.0f;
const float CollisionObject::DefaultHorizontalDampening = 0.75f;
const float CollisionObject::DefaultVerticalDampening = 1.0f;
const float CollisionObject::CollisionZThreshold = 20.0f;

CollisionObject* CollisionObject::create(const ValueMap& properties, std::vector<Vec2> points, CollisionType collisionType, Properties collisionProperties, Color4F debugColor)
{
	CollisionObject* instance = new CollisionObject(properties, points, collisionType, collisionProperties, debugColor);

	instance->autorelease();

	return instance;
}

CollisionObject* CollisionObject::create(std::vector<Vec2> points, CollisionType collisionType, Properties collisionProperties, Color4F debugColor)
{
	ValueMap valueMap = ValueMap();

	return CollisionObject::create(valueMap, points, collisionType, collisionProperties, debugColor);
}

CollisionObject::CollisionObject(const ValueMap& properties, std::vector<Vec2> points, CollisionType collisionType, Properties collisionProperties, Color4F debugColor) :
	super(properties)
{
	this->collisionType = collisionType;
	this->points = points;
	this->shape = this->determineShape();
	this->segments = AlgoUtils::buildSegmentsFromPoints(this->points);
	this->boundsRect = AlgoUtils::getPolygonRect(this->points);
	this->collidesWithTypes = std::set<CollisionType>();
	this->collisionStartEvents = std::map<CollisionType, std::vector<CollisionEvent>>();
	this->collisionSustainEvents = std::map<CollisionType, std::vector<CollisionEvent>>();
	this->collisionEndEvents = std::map<CollisionType, std::vector<CollisionEvent>>();
	this->collisionsRed = std::set<CollisionObject*>();
	this->collisionsBlack = std::set<CollisionObject*>();
	this->currentCollisions = &this->collisionsRed;
	this->previousCollisions = &this->collisionsBlack;
	this->collisionProperties = collisionProperties;
	this->physicsEnabled = true;
	this->gravityEnabled = collisionProperties.isDynamic;
	this->bindTarget = nullptr;
	this->debugColor = debugColor;
	this->debugDrawNode = nullptr;
	this->debugInfoSpawned = false;
	this->velocity = Vec2::ZERO;
	this->gravity = Vec2(0.0f, CollisionObject::DefaultGravity);
	this->horizontalDampening = 1.0f;
	this->verticalDampening = 1.0f;

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

		if (!this->points.empty())
		{
			if (this->points.size() == 2)
			{
				this->debugDrawNode->drawSegment(this->points.front(), this->points.back(), 1.0f, this->debugColor);
			}
			else
			{
				this->debugDrawNode->drawPolygon(this->points.data(), this->points.size(), Color4F(this->debugColor.r, this->debugColor.g, this->debugColor.b, 0.4f), 1.0f, this->debugColor);
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
		this->velocity += this->gravity * dt;
	}

	if (this->velocity != Vec2::ZERO)
	{
		// Apply dampening
		this->velocity.x *= this->horizontalDampening;
		this->velocity.y *= this->verticalDampening;

		// Enforce constraints by calling setter
		this->setVelocity(this->velocity);

		const float rotationInRad = GameUtils::getRotation(this) * float(M_PI) / 180.0f;
		const Vec2 positionUpdates = Vec2(
			(this->velocity.x * std::cos(rotationInRad) - this->velocity.y * std::sin(rotationInRad)) * dt,
			(this->velocity.x * std::sin(rotationInRad) + this->velocity.y * std::cos(rotationInRad)) * dt
		);

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
				CollisionResult collisionResult = CollisionResult::DoNothing;

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
			for (auto event : this->collisionEndEvents[collisionObject->getCollisionType()])
			{
				event.collisionEvent(CollisionData(collisionObject, dt));
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

const std::vector<cocos2d::Vec2>& CollisionObject::getPoints()
{
	return this->points;
}

CollisionObject::Shape CollisionObject::getShape()
{
	return this->shape;
}
	
CollisionType CollisionObject::getCollisionType()
{
	return this->collisionType;
}

const std::set<CollisionObject*>& CollisionObject::getCurrentCollisions()
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
		float progress = float(index) / float(segments);

		points.push_back(Vec2(
			std::cos(2.0f * float(M_PI) * progress) * radius,
			std::sin(2.0f * float(M_PI) * progress) * radius
		));
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

std::vector<Vec2> CollisionObject::createCapsulePolygon(Size size, float capsuleRadius)
{
	size.height = std::max(0.0f, size.height - capsuleRadius * 2.0f);

	std::vector<Vec2> points = std::vector<Vec2>();

	// Right side
	points.push_back(Vec2(size.width / 2.0f, size.height / 2.0f));
	points.push_back(Vec2(size.width / 2.0f, -size.height / 2.0f));

	// Bottom capsule
	points.push_back(Vec2(0.0f, -size.height / 2.0f - capsuleRadius));

	// Left side
	points.push_back(Vec2(-size.width / 2.0f, -size.height / 2.0f));
	points.push_back(Vec2(-size.width / 2.0f, size.height / 2.0f));

	// Top capsule
	points.push_back(Vec2(0.0f, size.height / 2.0f + capsuleRadius));

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

CollisionObject::Shape CollisionObject::determineShape()
{
	if (this->points.size() == 2)
	{
		return Shape::Segment;
	}
	else if (this->points.size() == 4)
	{
		int sameX = 0;
		int sameY = 0;
		Vec2 prior = this->points.back();

		for (auto point : this->points)
		{
			sameX += (point.x == prior.x ? 1 : 0);
			sameY += (point.y == prior.y ? 1 : 0);
		}

		return (sameX == 2 && sameY == 2) ? Shape::Rectangle : Shape::Quad;
	}

	return Shape::Polygon;
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
