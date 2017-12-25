#include "CollisionObject.h"

CollisionObject* CollisionObject::create(Size size)
{
	CollisionObject* collisionObject = new CollisionObject(PhysicsBody::createBox(size));

	collisionObject->autorelease();

	return collisionObject;
}

CollisionObject* CollisionObject::create(Vec2* points, int count)
{
	CollisionObject* collisionObject = new CollisionObject(PhysicsBody::createPolygon(points, count));

	collisionObject->autorelease();

	return collisionObject;
}

CollisionObject::CollisionObject(PhysicsBody* initPhysicsBody)
{
	this->physicsBody = initPhysicsBody;

	this->physicsBody->setDynamic(false);
	this->setPhysicsBody(this->physicsBody);

	this->InitializeListeners();
}

CollisionObject::~CollisionObject()
{
}

void CollisionObject::InitializeListeners()
{
	EventListenerPhysicsContact* contactListener = EventListenerPhysicsContact::create();

	contactListener->onContactBegin = CC_CALLBACK_1(CollisionObject::OnContactBegin, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void CollisionObject::SetCollisionGroup(CollisionGroup newCollisionGroup)
{
	this->collisionGroup = newCollisionGroup;
}

bool CollisionObject::OnContactBegin(PhysicsContact &contact)
{
	if (contact.getShapeA()->getBody()->getNode() != this && contact.getShapeB()->getBody()->getNode() != this)
	{
		return true;
	}

	PhysicsShape* other = nullptr;

	if (contact.getShapeA()->getBody()->getNode() == this)
	{
		other = contact.getShapeB();
	}
	else
	{
		other = contact.getShapeA();
	}

	switch (other->getContactTestBitmask())
	{
	case CollisionGroup::Solid:
		return true;
	case CollisionGroup::Water:
		this->physicsBody->setLinearDamping(8.0f);
		return false;
	case CollisionGroup::PassThrough:
		if (this->physicsBody->getVelocity().y > 0)
		{
			return false;
		}
		return true;
	default:
		return true;
	}
}
