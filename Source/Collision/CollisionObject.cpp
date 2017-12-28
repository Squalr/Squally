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

bool CollisionObject::contactBegin(CollisionData data)
{
	return true;
}

bool CollisionObject::contactUpdate(CollisionData data)
{
	return true;
}

bool CollisionObject::contactEnd(CollisionData data)
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
	CollisionData data = this->constructCollisionData(contact);

	if (data.other == nullptr)
	{
		return false;
	}

	return this->contactBegin(data);
}

bool CollisionObject::onContactUpdate(PhysicsContact &contact)
{
	CollisionData data = this->constructCollisionData(contact);

	if (data.other == nullptr)
	{
		return false;
	}

	return this->contactUpdate(data);
}

bool CollisionObject::onContactEnd(PhysicsContact &contact)
{
	CollisionData data = this->constructCollisionData(contact);

	if (data.other == nullptr)
	{
		return false;
	}

	return this->contactEnd(data);
}

CollisionObject::CollisionData CollisionObject::constructCollisionData(PhysicsContact& contact)
{
	CollisionObject::CollisionData collisionData = CollisionObject::CollisionData(nullptr, false);
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
	collisionData.isCollisionBelow = this->isContactBelow(other->getBody()->getNode(), contact);

	return collisionData;
}

bool CollisionObject::isContactBelow(Node* node, PhysicsContact& contact)
{
	for (int index = 0; index < contact.getContactData()->count; index++)
	{
		if (contact.getContactData()->points[index].y < node->getPositionY())
		{
			return true;
		}
	}

	return false;
}
