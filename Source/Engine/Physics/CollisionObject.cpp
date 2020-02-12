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
#include "Engine/GlobalDirector.h"
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
	this->collisionEvents = std::map<CollisionType, std::vector<CollisionEvent>>();
	this->collisionEndEvents = std::map<CollisionType, std::vector<CollisionEvent>>();
	this->currentCollisions = std::vector<CollisionObject*>();
	this->passThroughCandidates = std::map<CollisionObject*, CollisionData>();
	this->passThroughCandidatesIter = std::map<CollisionObject*, CollisionData>();
	this->isDynamic = isDynamic;
	this->physicsEnabled = true;
	this->gravityEnabled = false;
	this->gravityInversed = false;
	this->contactUpdateCallback = nullptr;
	this->bindTarget = nullptr;
	this->debugDrawNode = nullptr;
	this->debugInfoSpawned = false;

	/*
		this->physicsBody->setGravityEnable(false);
		this->physicsBody->setRotationEnable(canRotate);
		this->physicsBody->setDynamic(isDynamic);
		this->physicsBody->setContactTestBitmask(0);
		this->physicsBody->setCollisionBitmask(0);
	*/

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

	this->currentCollisions.clear();

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

void CollisionObject::initializeListeners()
{
	super::initializeListeners();
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
	
	/*
	if (this->physicsBody != nullptr)
	{
		this->physicsBody->setEnabled(false);
	}
	*/
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

	if (this->velocity != Vec2::ZERO)
	{
		// Apply dampening
		this->velocity.x *= this->horizontalDampening;
		this->velocity.y *= this->verticalDampening;

		// Enforce constraints by calling setter
		this->setVelocity(this->velocity);

		Vec2 updatedPosition = this->getThisOrBindPosition();

		updatedPosition.x += this->velocity.x * dt;
		updatedPosition.y += this->velocity.y * dt;

		this->setThisOrBindPosition(updatedPosition);
	}

	CollisionCorrections collisionCorrections = CollisionCorrections();

	this->currentCollisions.clear();

	for (auto events : this->collisionEvents)
	{
		CollisionType eventCollisionType = events.first;

		for (auto collisionObject : CollisionObject::CollisionObjects[eventCollisionType])
		{
			if (this->collidesWith(collisionObject))
			{
				this->currentCollisions.push_back(collisionObject);

				CollisionResult collisionResult;

				for (auto event : events.second)
				{
					CollisionResult nextResult = event.collisionEvent(CollisionData(collisionObject));

					collisionResult = nextResult == CollisionResult::DoNothing ? collisionResult : nextResult;
				}

				if (this->isDynamic && collisionResult == CollisionResult::CollideWithPhysics)
				{
					this->applyCollisionCorrections(collisionObject);
				}
			}
		}
	}

	/*
	if (collisionCorrections.normalForce != Vec2::ZERO)
	{
		collisionCorrections.normalForce.normalize();
		Vec2 normalVelocity = this->velocity;

		normalVelocity.x *= collisionCorrections.normalForce.x;
		normalVelocity.y *= collisionCorrections.normalForce.y;

		if (this->bindTarget == nullptr)
		{
			this->setPositionX(this->getPositionX() + normalVelocity.x * dt);
			this->setPositionY(this->getPositionY() + normalVelocity.y * dt);
		}
		else
		{	this->bindTarget->setPositionX(this->bindTarget->getPositionX() + normalVelocity.x * dt);
			this->bindTarget->setPositionY(this->bindTarget->getPositionY() + normalVelocity.y * dt);
		}
	}*/
}

void CollisionObject::setContactUpdateCallback(std::function<void(const std::vector<CollisionObject*>& currentCollisions, float dt)> contactUpdateCallback)
{
	this->contactUpdateCallback = contactUpdateCallback;
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

void CollisionObject::setPosition(const Vec2& position)
{
	super::setPosition(position);

	/*
	if (this->physicsBody != nullptr)
	{
		this->physicsBody->setPositionInterruptPhysics(Vec2::ZERO);
	}*/
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

std::vector<CollisionObject*> CollisionObject::getCurrentCollisions()
{
	return this->currentCollisions;
}

bool CollisionObject::isCollidingWith(CollisionObject* collisionObject)
{
	return std::find(this->currentCollisions.begin(), this->currentCollisions.end(), collisionObject) != this->currentCollisions.end();
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
		this->addCollisionEvent(collisionType, this->collisionEvents, CollisionEvent(onCollision));
	}
}

void CollisionObject::whenStopsCollidingWith(std::vector<CollisionType> collisionTypes, std::function<CollisionResult(CollisionData)> onCollisionEnd)
{
	for (auto collisionType : collisionTypes)
	{
		this->addCollisionEvent(collisionType, this->collisionEndEvents, CollisionEvent(onCollisionEnd));
	}
}

void CollisionObject::addCollisionEvent(CollisionType collisionType, std::map<CollisionType, std::vector<CollisionEvent>>& eventMap, CollisionEvent onCollision)
{
	eventMap[collisionType].push_back(onCollision);
}

std::vector<Vec2> CollisionObject::createCircle(float radius, int segments)
{
	return std::vector<Vec2>();
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

bool CollisionObject::collidesWith(CollisionObject* collisionObject)
{
	// Check for easy disqualifications
	if (collisionObject == this
		|| collisionObject == nullptr
		|| !this->physicsEnabled
		|| !collisionObject->physicsEnabled
		|| !this->isWithinZThreshold(collisionObject))
	{
		return false;
	}
	
	Rect thisRect = this->boundsRect;
	Rect otherRect = collisionObject->boundsRect;

	Vec2 thisCoords = GameUtils::getWorldCoords(this);
	Vec2 otherCoords = GameUtils::getWorldCoords(collisionObject);

	thisRect.origin += thisCoords;
	otherRect.origin += otherCoords;

	if (thisRect.intersectsRect(otherRect))
	{
		std::tuple<cocos2d::Vec2, cocos2d::Vec2> currentSegment;
		std::tuple<cocos2d::Vec2, cocos2d::Vec2> otherSegment;

		for (auto segment : this->segments)
		{
			currentSegment = std::make_tuple(thisCoords + std::get<0>(segment), thisCoords + std::get<1>(segment));

			for (auto otherSegment : collisionObject->segments)
			{
				otherSegment = std::make_tuple(otherCoords + std::get<0>(otherSegment), otherCoords + std::get<1>(otherSegment));

				if (AlgoUtils::doSegmentsIntersect(currentSegment, otherSegment))
				{
					return true;
				}
			}
		}
	}

	return false;
}

void CollisionObject::applyCollisionCorrections(CollisionObject* collisionObject)
{
	Vec2 thisCoords = GameUtils::getWorldCoords(this);
	Vec2 otherCoords = GameUtils::getWorldCoords(collisionObject);

	std::tuple<cocos2d::Vec2, cocos2d::Vec2> currentSegment;
	std::tuple<cocos2d::Vec2, cocos2d::Vec2> otherSegment;

	Vec2 correctionOffset = Vec2::ZERO;

	for (auto currentSegment : this->segments)
	{
		currentSegment = std::make_tuple(thisCoords + std::get<0>(currentSegment), thisCoords + std::get<1>(currentSegment));

		for (auto otherSegment : collisionObject->segments)
		{
			otherSegment = std::make_tuple(otherCoords + std::get<0>(otherSegment), otherCoords + std::get<1>(otherSegment));

			if (AlgoUtils::doSegmentsIntersect(currentSegment, otherSegment))
			{
				Vec2 intersectionPoint = AlgoUtils::getLineIntersectionPoint(currentSegment, otherSegment);

				// Other object is static! We need to push this object away from it.
				if (!collisionObject->isDynamic)
				{
					float thisDistanceA = std::get<0>(currentSegment).distance(intersectionPoint);
					float thisDistanceB = std::get<1>(currentSegment).distance(intersectionPoint);
					float otherDistanceA = std::get<0>(otherSegment).distance(intersectionPoint);
					float otherDistanceB = std::get<1>(otherSegment).distance(intersectionPoint);

					Vec2 updatedPosition = this->getThisOrBindPosition();
					Vec2 correction = Vec2::ZERO;

					if (std::min(thisDistanceA, thisDistanceB) < std::min(otherDistanceA, otherDistanceB))
					{
						// Case 1: The end of this segment is close to the intersection point. Snap the end of this segment to intersect the other segment.
						if (thisDistanceA < thisDistanceB)
						{
							// correction = intersectionPoint - std::get<0>(currentSegment);
							correction = std::get<0>(currentSegment) - intersectionPoint;
						}
						else
						{
							correction = intersectionPoint - std::get<1>(currentSegment);
							// correction = std::get<1>(currentSegment) - intersectionPoint;
						}
					}
					else
					{
						// Case 2: The end of the other segment is closer to the intersection point. The other object can't snap since it's dynamic,
						// so instead we need to push this object away by a calculated amount
					}

					thisCoords += correction;
					this->setThisOrBindPosition(updatedPosition + correction);
				}
			}
		}
	}
}

void CollisionObject::updateCollisionCorrections(CollisionObject* collisionObject, CollisionCorrections* collisionCorrections)
{
	Vec2 thisCoords = GameUtils::getWorldCoords(this);
	Vec2 otherCoords = GameUtils::getWorldCoords(collisionObject);

	std::tuple<cocos2d::Vec2, cocos2d::Vec2> currentSegment;
	std::tuple<cocos2d::Vec2, cocos2d::Vec2> otherSegment;

	for (auto segment : this->segments)
	{
		currentSegment = std::make_tuple(thisCoords + std::get<0>(segment), thisCoords + std::get<1>(segment));

		for (auto otherSegment : collisionObject->segments)
		{
			otherSegment = std::make_tuple(otherCoords + std::get<0>(otherSegment), otherCoords + std::get<1>(otherSegment));

			if (AlgoUtils::doSegmentsIntersect(currentSegment, otherSegment))
			{
				collisionCorrections->normalForce += AlgoUtils::getSegmentNormal(currentSegment);
			}
		}
	}
}

bool CollisionObject::isWithinZThreshold(CollisionObject* collisionObject)
{
	const float thisDepth = GameUtils::getDepth(this);
	const float otherDepth = GameUtils::getDepth(collisionObject);

	if (std::abs(thisDepth - otherDepth) >= CollisionObject::CollisionZThreshold)
	{
		return false;
	}

	return true;
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
