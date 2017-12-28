#include "CollisionObject.h"

CollisionObject::CollisionObject()
{
}

CollisionObject::~CollisionObject()
{
}

void CollisionObject::init(PhysicsBody* initPhysicsBody, CollisionGroup initCollisionGroup, CollisionGroup initCollidesWith)
{
	this->physicsBody = initPhysicsBody;
	this->collisionGroup = initCollisionGroup;
	this->collidesWith = initCollidesWith;

	this->physicsBody->setCategoryBitmask(this->collisionGroup);
	this->physicsBody->setCollisionBitmask(this->collidesWith);
	this->physicsBody->setContactTestBitmask(this->collidesWith);

	this->physicsBody->setRotationEnable(false);
	this->setPhysicsBody(initPhysicsBody);

	this->initializeEventListeners();
}

// Constructor for static objects
void CollisionObject::init(PhysicsBody* initPhysicsBody, CollisionGroup initCollisionGroup)
{
	this->physicsBody = initPhysicsBody;
	this->collisionGroup = initCollisionGroup;
	this->collidesWith = CollisionGroup::SET_All;

	this->physicsBody->setCategoryBitmask(this->collisionGroup);
	this->physicsBody->setCollisionBitmask(this->collidesWith);
	this->physicsBody->setContactTestBitmask(this->collidesWith);

	this->physicsBody->setRotationEnable(false);
	this->physicsBody->setDynamic(false);
	this->setPhysicsBody(initPhysicsBody);

	this->initializeEventListeners();
}

Vec2 CollisionObject::getVelocity()
{
	return this->physicsBody->getVelocity();
}

void CollisionObject::setVelocity(Vec2 velocity)
{
	this->physicsBody->setVelocity(velocity);
}

CollisionGroup CollisionObject::getCollisionGroup()
{
	return this->collisionGroup;
}

bool CollisionObject::contactBegin(CollisionObject* other)
{
	return true;
}

bool CollisionObject::contactUpdate(CollisionObject* other)
{
	return true;
}

bool CollisionObject::contactEnd(CollisionObject* other)
{
	return true;
}

void CollisionObject::initializeEventListeners()
{
	EventListenerPhysicsContact* contactListener = EventListenerPhysicsContact::create();

	contactListener->onContactBegin = CC_CALLBACK_1(CollisionObject::onContactBegin, this);
	contactListener->onContactPreSolve = CC_CALLBACK_1(CollisionObject::onContactUpdate, this);
	// contactListener->onContactPostSolve = CC_CALLBACK_1(CollisionObject::onContactUpdate, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(CollisionObject::onContactEnd, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}

bool CollisionObject::onContactBegin(PhysicsContact &contact)
{
	PhysicsShape* other = this->getCollidingObject(this->physicsBody, contact);

	if (other == nullptr)
	{
		return false;
	}

	return this->contactBegin((CollisionObject*)other->getBody());
}

bool CollisionObject::onContactUpdate(PhysicsContact &contact)
{
	PhysicsShape* other = this->getCollidingObject(this->physicsBody, contact);

	if (other == nullptr)
	{
		return false;
	}

	return this->contactUpdate((CollisionObject*)other->getBody());
}

bool CollisionObject::onContactEnd(PhysicsContact &contact)
{
	PhysicsShape* other = this->getCollidingObject(this->physicsBody, contact);

	if (other == nullptr)
	{
		return false;
	}

	return this->contactEnd((CollisionObject*)other->getBody());
}

PhysicsShape* CollisionObject::getCollidingObject(PhysicsBody* self, PhysicsContact& contact)
{
	if (contact.getShapeA()->getBody() != self && contact.getShapeB()->getBody() != self)
	{
		return false;
	}

	PhysicsShape* other = nullptr;

	if (contact.getShapeA()->getBody() == self)
	{
		other = contact.getShapeB();
	}
	else
	{
		other = contact.getShapeA();
	}

	return other;
}
