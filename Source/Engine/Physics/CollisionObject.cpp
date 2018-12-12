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

const std::string CollisionObject::MapKeyTypeCollision = "collision";

CollisionObject::CollisionObject(ValueMap* initProperties, PhysicsBody* initPhysicsBody, std::string deserializedCollisionName, bool isDynamic, bool canRotate) :
	CollisionObject(initProperties, initPhysicsBody, (CollisionType)0, isDynamic, canRotate)
{
	// Fire event, allowing for the game to map the deserialized collision string type (ie 'solid') to a unique integer identifier for CollisionType
	CollisionMappingEvents::requestCollisionMapKeyMapping(CollisionMappingEvents::CollisionMapRequestArgs(deserializedCollisionName, this));

	// Fire event, allowing for the game to map what this collision object collides with
	if (this->physicsBody != nullptr)
	{
		CollisionMappingEvents::requestAllowedCollisionMapping(CollisionMappingEvents::AllowedCollisionsRequestArgs(this->physicsBody->getCollisionBitmask(), this));
	}
}

CollisionObject::CollisionObject(ValueMap* initProperties, PhysicsBody* initPhysicsBody, CollisionType collisionType, bool isDynamic, bool canRotate) :
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

	this->setCollisionType(collisionType);

	// Fire event, allowing for the game to map what this collision object collides with
	CollisionMappingEvents::requestAllowedCollisionMapping(CollisionMappingEvents::AllowedCollisionsRequestArgs(collisionType, this));
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
	return this->physicsBody == nullptr ? (CollisionType)0 : (CollisionType)this->physicsBody->getCategoryBitmask();
}

void CollisionObject::addPhysicsShape(cocos2d::PhysicsShape* shape)
{
	if (this->physicsBody != nullptr)
	{
		this->physicsBody->addShape(shape);
	}
}

void CollisionObject::allowCollisionWith(std::vector<CollisionType> collisionTypes)
{
	CollisionType bitmask = 0;

	for (auto it = collisionTypes.begin(); it != collisionTypes.end(); it++)
	{
		bitmask |= *it;
	}

	this->physicsBody->setContactTestBitmask(this->physicsBody->getContactTestBitmask() | (int)bitmask);
	this->physicsBody->setCollisionBitmask(this->physicsBody->getCollisionBitmask() | (int)bitmask);
}

void CollisionObject::whenCollidesWith(std::vector<CollisionType> collisionTypes, std::function<CollisionResult(CollisionData)> onCollision)
{
	for (auto it = collisionTypes.begin(); it != collisionTypes.end(); it++)
	{
		CollisionType collisionType = *it;

		if (this->collisionEvents.find(collisionType) != this->collisionEvents.end())
		{
			this->collisionEvents[collisionType] = std::vector<std::function<CollisionResult(CollisionData)>>();
		}

		this->collisionEvents[collisionType].push_back(onCollision);
	}
}

void CollisionObject::whenStopsCollidingWith(std::vector<CollisionType> collisionTypes, std::function<CollisionResult(CollisionData)> onCollisionEnd)
{
	for (auto it = collisionTypes.begin(); it != collisionTypes.end(); it++)
	{
		CollisionType collisionType = *it;

		if (this->collisionEndEvents.find(collisionType) != this->collisionEndEvents.end())
		{
			this->collisionEndEvents[collisionType] = std::vector<std::function<CollisionResult(CollisionData)>>();
		}

		this->collisionEndEvents[collisionType].push_back(onCollisionEnd);
	}
}

bool CollisionObject::onContactBegin(PhysicsContact &contact)
{
	// Currently we are not distinguishing between these two
	return this->onContactUpdate(contact);
}

bool CollisionObject::onContactUpdate(PhysicsContact &contact)
{
	return this->runContactEvents(contact, this->collisionEvents);
}

bool CollisionObject::onContactEnd(PhysicsContact &contact)
{
	return this->runContactEvents(contact, this->collisionEndEvents);
}

bool CollisionObject::runContactEvents(cocos2d::PhysicsContact& contact, std::map<CollisionType, std::vector<std::function<CollisionResult(CollisionData)>>> eventMap)
{
	CollisionObject* other = this->getOtherObject(contact);
	CollisionResult result = CollisionResult::CollideWithPhysics;

	if (other != nullptr)
	{
		CollisionType collisionType = other->getCollisionType();

		if (eventMap.find(collisionType) != eventMap.end())
		{
			CollisionData collisionData = this->constructCollisionData(contact);
			std::vector<std::function<CollisionResult(CollisionData)>> events = eventMap[collisionType];

			for (auto eventIt = events.begin(); eventIt != events.end(); eventIt++)
			{
				CollisionResult eventResult = (*eventIt)(collisionData);

				// Doing nothing takes precidence
				result = (result == CollisionResult::DoNothing) ? CollisionResult::DoNothing : eventResult;
			}
		}
	}

	return (result == CollisionResult::CollideWithPhysics ? true : false);
}

CollisionObject* CollisionObject::getOtherObject(cocos2d::PhysicsContact& contact)
{
	PhysicsShape* other = nullptr;

	if (contact.getShapeA()->getBody() != this->physicsBody && contact.getShapeB()->getBody() != this->physicsBody)
	{
		return nullptr;
	}

	if (contact.getShapeA()->getBody() == this->physicsBody)
	{
		other = contact.getShapeB();
	}
	else
	{
		other = contact.getShapeA();
	}

	return dynamic_cast<CollisionObject*>(other->getBody()->getNode());
}

CollisionObject::CollisionData CollisionObject::constructCollisionData(PhysicsContact& contact)
{
	CollisionObject::CollisionData collisionData = CollisionObject::CollisionData(nullptr, Vec2::ZERO, CollisionObject::CollisionDirection::None, nullptr, 0);
	
	collisionData.other = this->getOtherObject(contact);

	if (collisionData.other == nullptr)
	{
		return collisionData;
	}

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
