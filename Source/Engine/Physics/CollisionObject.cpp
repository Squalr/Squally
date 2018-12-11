#include "CollisionObject.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"
#include "cocos/base/CCValue.h"
#include "cocos/physics/CCPhysicsBody.h"
#include "cocos/physics/CCPhysicsContact.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

std::string CollisionObject::MapKeyTypeCollision = "collision";

const std::string CollisionObject::RequestCollisionMappingEvent = "request_collision_mapping";

void CollisionObject::requestCollisionMapping(CollisionMapRequestArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		CollisionObject::RequestCollisionMappingEvent,
		&args
	);
}

CollisionObject::CollisionObject(ValueMap* initProperties, PhysicsBody* initPhysicsBody, DeserializedCollisionName deserializedCollisionName, bool isDynamic, bool canRotate) :
	HackableObject(initProperties)
{
	this->physicsBody = initPhysicsBody;
	this->collisionEvents = std::map<CollisionType, std::vector<std::function<CollisionResult(CollisionData)>>>();
	this->collisionEndEvents = std::map<CollisionType, std::vector<std::function<CollisionResult(CollisionData)>>>();

	if (this->physicsBody != nullptr)
	{
		this->physicsBody->setRotationEnable(canRotate);
		this->physicsBody->setDynamic(isDynamic);
		this->setPhysicsBody(initPhysicsBody);
	}

	// Fire event, allowing for the game to map what this collision object collides with
	CollisionObject::requestCollisionMapping(CollisionObject::CollisionMapRequestArgs(deserializedCollisionName, this));
}

CollisionObject::CollisionObject(ValueMap* initProperties, PhysicsBody* initPhysicsBody, CollisionType collisionType, bool isDynamic, bool canRotate) :
	HackableObject(initProperties)
{
	this->physicsBody = initPhysicsBody;

	if (this->physicsBody != nullptr)
	{
		this->physicsBody->setRotationEnable(canRotate);
		this->physicsBody->setDynamic(isDynamic);
		this->setPhysicsBody(initPhysicsBody);
	}

	this->setCollisionType(collisionType);
}

CollisionObject::~CollisionObject()
{
}

void CollisionObject::onEnter()
{
	HackableObject::onEnter();

	this->scheduleUpdate();
}

void CollisionObject::initializeListeners()
{
	HackableObject::initializeListeners();

	EventListenerPhysicsContact* contactListener = EventListenerPhysicsContact::create();

	contactListener->onContactBegin = CC_CALLBACK_1(CollisionObject::onContactBegin, this);
	contactListener->onContactPreSolve = CC_CALLBACK_1(CollisionObject::onContactUpdate, this);
	contactListener->onContactPostSolve = CC_CALLBACK_1(CollisionObject::onContactUpdate, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(CollisionObject::onContactEnd, this);

	this->addEventListener(contactListener);
}

void CollisionObject::setCollisionType(CollisionType collisionType)
{
	if (this->physicsBody != nullptr)
	{
		this->physicsBody->setCategoryBitmask(collisionType);
	}
}

void CollisionObject::update(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 pos = this->getPosition();
	Size STOP_PHYSICS_OFFSET = visibleSize / 2.0f;

	if (this->physicsBody != nullptr && this->physicsBody->isDynamic())
	{
		Vec2 cameraPosition = GameCamera::getInstance()->getCameraPosition();

		if (pos.x > cameraPosition.x + visibleSize.width + STOP_PHYSICS_OFFSET.width ||
			pos.x < cameraPosition.x - STOP_PHYSICS_OFFSET.width ||
			pos.y > cameraPosition.y + visibleSize.height + STOP_PHYSICS_OFFSET.height ||
			pos.y < cameraPosition.y - STOP_PHYSICS_OFFSET.height)
		{
			// Bypass setter to force disable physics for this object
			this->physicsBody->setEnabled(false);
		}
		else
		{
			// Use setter such that if physics was disabled for a reason other than being off-screen, we do not overwrite that
			this->setPhysicsEnabled(this->physicsEnabled);
		}
	}
}

void CollisionObject::setPhysicsEnabled(bool enabled)
{
	this->physicsEnabled = enabled;

	if (this->physicsBody != nullptr)
	{
		this->physicsBody->setEnabled(enabled);
	}
}

Vec2 CollisionObject::getVelocity()
{
	return this->physicsBody == nullptr ? Vec2::ZERO : this->physicsBody->getVelocity();
}

void CollisionObject::setVelocity(Vec2 velocity)
{
	if (this->physicsBody != nullptr)
	{
		this->physicsBody->setVelocity(velocity);
	}
}

CollisionType CollisionObject::getCollisionType()
{
	return this->physicsBody == nullptr ? 0 : this->physicsBody->getCategoryBitmask();
}

void CollisionObject::whenCollidesWith(CollisionType collisionType, std::function<CollisionResult(CollisionData)> onCollision)
{
	this->whenCollidesWith(std::vector<CollisionType>({ collisionType }), onCollision);
}

void CollisionObject::whenCollidesWith(std::vector<CollisionType> collisionTypes, std::function<CollisionResult(CollisionData)> onCollision)
{
	if (this->physicsBody != nullptr)
	{
		CollisionType bitmask = 0;

		for (auto it = collisionTypes.begin(); it != collisionTypes.end(); it++)
		{
			bitmask |= *it;
		}

		if (std::find(this->collisionEvents.begin(), this->collisionEvents.end(), bitmask) != this->collisionEvents.end())
		{
			this->collisionEvents[bitmask] = std::vector<std::function<CollisionResult(CollisionData)>>();
		}

		this->collisionEvents[bitmask].push_back(onCollision);

		this->physicsBody->setCollisionBitmask(this->physicsBody->getCollisionBitmask() | (int)bitmask);
		this->physicsBody->setContactTestBitmask(0xFFFFFFFF);
	}
}

void CollisionObject::whenStopsCollidingWith(CollisionType collisionType, std::function<CollisionResult(CollisionData)> onCollisionEnd)
{
	this->whenStopsCollidingWith(std::vector<CollisionType>({ collisionType }), onCollisionEnd);
}

void CollisionObject::whenStopsCollidingWith(std::vector<CollisionType> collisionTypes, std::function<CollisionResult(CollisionData)> onCollisionEnd)
{
	if (this->physicsBody != nullptr)
	{
		CollisionType bitmask = 0;
		
		for (auto it = collisionTypes.begin(); it != collisionTypes.end(); it++)
		{
			bitmask |= *it;
		}

		if (std::find(this->collisionEndEvents.begin(), this->collisionEndEvents.end(), bitmask) != this->collisionEndEvents.end())
		{
			this->collisionEndEvents[bitmask] = std::vector<std::function<CollisionResult(CollisionData)>>();
		}

		this->collisionEndEvents[bitmask].push_back(onCollisionEnd);

		this->physicsBody->setCollisionBitmask(this->physicsBody->getCollisionBitmask() | (int)bitmask);
		this->physicsBody->setContactTestBitmask(0xFFFFFFFF);
	}
}

bool CollisionObject::onContactBegin(PhysicsContact &contact)
{
	// Currently we are not distinguishing between these two
	return this->onContactUpdate(contact);
}

bool CollisionObject::onContactUpdate(PhysicsContact &contact)
{
	CollisionData collisionData = this->constructCollisionData(contact);
	CollisionResult result = CollisionResult::DoNothing;

	for (auto it = this->collisionEvents.begin(); it != this->collisionEvents.end(); it++)
	{
		for (auto eventIt = (*it).second.begin(); eventIt != (*it).second.end(); eventIt++)
		{
			CollisionResult eventResult = (*eventIt)(collisionData);
			result = result == CollisionResult::CollideWithPhysics ? CollisionResult::CollideWithPhysics : eventResult;
		}
	}

	return result == CollisionResult::CollideWithPhysics ? true : false;
}

bool CollisionObject::onContactEnd(PhysicsContact &contact)
{
	CollisionData collisionData = this->constructCollisionData(contact);
	CollisionResult result = CollisionResult::DoNothing;

	for (auto it = this->collisionEndEvents.begin(); it != this->collisionEndEvents.end(); it++)
	{
		for (auto eventIt = (*it).second.begin(); eventIt != (*it).second.end(); eventIt++)
		{
			CollisionResult eventResult = (*eventIt)(collisionData);
			result = result == CollisionResult::CollideWithPhysics ? CollisionResult::CollideWithPhysics : eventResult;
		}
	}

	return result == CollisionResult::CollideWithPhysics ? true : false;
}

CollisionObject::CollisionData CollisionObject::constructCollisionData(PhysicsContact& contact)
{
	CollisionObject::CollisionData collisionData = CollisionObject::CollisionData(nullptr, Vec2::ZERO, CollisionObject::CollisionDirection::None, nullptr, 0);
	PhysicsShape* other = nullptr;

	if (contact.getShapeA()->getBody() != this->physicsBody && contact.getShapeB()->getBody() != this->physicsBody)
	{
		return collisionData;
	}

	if (contact.getShapeA()->getBody() == this->physicsBody)
	{
		other = contact.getShapeB();
	}
	else
	{
		other = contact.getShapeA();
	}

	if (other == nullptr)
	{
		return collisionData;
	}

	collisionData.other = (CollisionObject*)other->getBody()->getNode();
	collisionData.normal = contact.getContactData()->normal;
	collisionData.pointCount = contact.getContactData()->count;
	Vec2 cameraPosition = GameCamera::getInstance()->getCameraPosition();

	// Convert collision coordinates to level coordinates
	for (int index = 0; index < collisionData.pointCount; index++)
	{
		collisionData.points[index] = Vec2(contact.getContactData()->points[index].x + cameraPosition.x, contact.getContactData()->points[index].y + cameraPosition.y);
	}

	// Determines how large the
	const float sensitivity = 16.0f;

	// Determine direction of collision
	if (collisionData.pointCount == 2)
	{
		// Horizontal collision
		if (collisionData.points[0].x == collisionData.points[1].x)
		{
			if (abs(collisionData.points[0].y - collisionData.points[1].y) > sensitivity)
			{
				if (this->getPositionX() < collisionData.other->getPositionX())
				{
					collisionData.direction = CollisionDirection::Right;
				}
				else
				{
					collisionData.direction = CollisionDirection::Left;
				}
			}
			else if (this->getPositionY() >= std::max(collisionData.points[0].y, collisionData.points[1].y))
			{
				if (this->getPositionX() < collisionData.other->getPositionX())
				{
					collisionData.direction = CollisionDirection::StepRight;
				}
				else
				{
					collisionData.direction = CollisionDirection::StepLeft;
				}
			}
		}
		// Vertical collision
		else if (collisionData.points[0].y == collisionData.points[1].y &&
			abs(collisionData.points[0].x - collisionData.points[1].x) > sensitivity)
		{
			if (this->getPositionY() < collisionData.other->getPositionY())
			{
				collisionData.direction = CollisionDirection::Up;
			}
			else
			{
				collisionData.direction = CollisionDirection::Down;
			}
		}
	}

	return collisionData;
}
