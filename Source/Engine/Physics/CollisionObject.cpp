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
	this->boundsRect = AlgoUtils::getPolygonRect(this->shape);
	this->collisionEvents = std::map<CollisionType, std::vector<CollisionEvent>>();
	this->collisionEndEvents = std::map<CollisionType, std::vector<CollisionEvent>>();
	this->currentCollisions = std::vector<CollisionObject*>();
	this->passThroughCandidates = std::map<CollisionObject*, CollisionData>();
	this->passThroughCandidatesIter = std::map<CollisionObject*, CollisionData>();
	this->gravityEnabled = true;
	this->gravityInversed = true;
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
	Vec2 velocity = this->getVelocity();

	// Apply gravity
	/*
	if (this->gravityEnabled && scene != nullptr && scene->getPhysicsWorld() != nullptr)
	{
		const Vec2 gravity = Director::getInstance()->getRunningScene()->getPhysicsWorld()->getGravity();

		velocity.x += gravity.x * dt;

		if (this->gravityInversed)
		{
			velocity.y += gravity.y * dt;
		}
		else
		{
			velocity.y -= gravity.y * dt;
		}
	}
	*/

	const Vec2 oldPosition = this->bindTarget == nullptr ? this->getPosition() : this->bindTarget->getPosition();

	if (velocity != Vec2::ZERO)
	{
		// Apply dampening
		velocity.x *= this->horizontalDampening;
		velocity.y *= this->verticalDampening;

		this->setVelocity(velocity);

		if (this->bindTarget == nullptr)
		{
			this->setPositionX(this->getPositionX() + velocity.x * dt);
			this->setPositionY(this->getPositionY() + velocity.y * dt);
		}
		else
		{	this->bindTarget->setPositionX(this->bindTarget->getPositionX() + velocity.x * dt);
			this->bindTarget->setPositionY(this->bindTarget->getPositionY() + velocity.y * dt);
		}
	}

	CollisionResult result = CollisionResult::DoNothing;

	for (auto events : this->collisionEvents)
	{
		CollisionType eventCollisionType = events.first;

		for (auto collisionObject : CollisionObject::CollisionObjects[eventCollisionType])
		{
			if (this->collidesWith(collisionObject))
			{
				for (auto event : events.second)
				{
					CollisionResult eventResult = event.collisionEvent(CollisionData(collisionObject));

					result = eventResult == CollisionResult::DoNothing ? result : eventResult;
				}
			}
		}
	}

	if (result == CollisionResult::CollideWithPhysics)
	{
		if (this->bindTarget == nullptr)
		{
			this->setPosition(oldPosition);
		}
		else
		{	this->bindTarget->setPosition(oldPosition);
		}
	}
}

void CollisionObject::setContactUpdateCallback(std::function<void(const std::vector<CollisionObject*>& currentCollisions, float dt)> contactUpdateCallback)
{
	this->contactUpdateCallback = contactUpdateCallback;
}

void CollisionObject::setPhysicsEnabled(bool enabled)
{
	/*
	if (this->physicsBody != nullptr)
	{
		this->physicsBody->setEnabled(enabled);
	}
	*/
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

void CollisionObject::setAngularVelocity(float angularVelocity)
{
	/*
	if (this->physicsBody != nullptr)
	{
		this->physicsBody->setAngularVelocity(angularVelocity);
	}
	*/
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

/*
bool CollisionObject::onContactBegin(PhysicsContact &contact)
{
	// Currently we are not distinguishing between begin/update
	return this->onContactUpdate(contact);
}

bool CollisionObject::onContactUpdate(PhysicsContact &contact)
{
	CollisionData collisionData = this->constructCollisionData(contact);

	if (!this->isWithinZThreshold(collisionData))
	{
		this->passThroughCandidates[collisionData.other] = collisionData;
		return false;
	}
	
	if (std::find(this->currentCollisions.begin(), this->currentCollisions.end(), collisionData.other) == this->currentCollisions.end())
	{
		this->currentCollisions.push_back(collisionData.other);
	}

	return this->runContactEvents(this->collisionEvents, CollisionResult::CollideWithPhysics, collisionData);
}

bool CollisionObject::onContactRetry(CollisionData& collisionData)
{
	if (!this->isWithinZThreshold(collisionData))
	{
		return false;
	}
	
	if (std::find(this->currentCollisions.begin(), this->currentCollisions.end(), collisionData.other) == this->currentCollisions.end())
	{
		this->currentCollisions.push_back(collisionData.other);
	}

	this->runContactEvents(this->collisionEvents, CollisionResult::CollideWithPhysics, collisionData);

	return true;
}

bool CollisionObject::onContactEnd(PhysicsContact &contact)
{
	CollisionData collisionData = this->constructCollisionData(contact);

	if (this->passThroughCandidates.find(collisionData.other) != this->passThroughCandidates.end())
	{
		this->passThroughCandidates.erase(collisionData.other);
	}

	this->currentCollisions.erase(
		std::remove(this->currentCollisions.begin(), this->currentCollisions.end(), collisionData.other), this->currentCollisions.end()
	);

	if (!this->isWithinZThreshold(collisionData))
	{
		return false;
	}

	return this->runContactEvents(this->collisionEndEvents, CollisionResult::DoNothing, collisionData);
}
*/

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

bool CollisionObject::runContactEvents(std::map<CollisionType, std::vector<CollisionEvent>>& eventMap, CollisionResult defaultResult, const CollisionData& collisionData)
{
	/*
	if (this->physicsBody != nullptr && !this->physicsBody->isEnabled())
	{
		return false;
	}
	*/

	CollisionResult result = defaultResult;

	if (collisionData.other != nullptr && this->isWithinZThreshold(collisionData))
	{
		CollisionType collisionType = collisionData.other->getCollisionType();

		if (eventMap.find(collisionType) != eventMap.end())
		{
			std::vector<CollisionEvent> events = eventMap[collisionType];

			for (auto eventIt = events.begin(); eventIt != events.end(); eventIt++)
			{
				CollisionResult eventResult = (*eventIt).collisionEvent(collisionData);

				// Anti-default takes precidence
				result = (eventResult != defaultResult) ? eventResult : result;
			}
		}
	}

	return (result == CollisionResult::CollideWithPhysics ? true : false);
}

bool CollisionObject::collidesWith(CollisionObject* collisionObject)
{
	if (collisionObject == this)
	{
		return false;
	}
	
	Rect thisRect = this->boundsRect;
	Rect otherRect = collisionObject->boundsRect;

	thisRect.origin += GameUtils::getWorldCoords(this);
	otherRect.origin += GameUtils::getWorldCoords(collisionObject);

	bool intersects = thisRect.intersectsRect(otherRect);

	if (intersects == true)
	{
		return true;
	}

	return false;

	/*
	if (this->getParent() == collisionObject->getParent())
	{
		return this->boundsRect.intersectsRect(collisionObject->boundsRect);
	}
	else
	{
		Rect thisRect = this->boundsRect;
		Rect otherRect = collisionObject->boundsRect;

		thisRect.origin += GameUtils::getWorldCoords(this);
		otherRect.origin += GameUtils::getWorldCoords(collisionObject);

		return thisRect.intersectsRect(otherRect);
	}*/
}

bool CollisionObject::isWithinZThreshold(const CollisionData& collisionData)
{
	const float thisDepth = GameUtils::getDepth(this);
	const float otherDepth = GameUtils::getDepth(collisionData.other);

	if (std::abs(thisDepth - otherDepth) >= CollisionObject::CollisionZThreshold)
	{
		return false;
	}

	return true;
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
