#include "CollisionEventDispatcher.h"

#include "cocos/physics/CCPhysicsContact.h"

#include "Engine/GlobalDirector.h"

using namespace cocos2d;

CollisionEventDispatcher* CollisionEventDispatcher::instance = nullptr;

void CollisionEventDispatcher::registerGlobalNode()
{
	if (CollisionEventDispatcher::instance == nullptr)
	{
		CollisionEventDispatcher::instance = new CollisionEventDispatcher();
		CollisionEventDispatcher::instance->autorelease();
	}

	GlobalDirector::registerGlobalNode(CollisionEventDispatcher::instance);
}

void CollisionEventDispatcher::initializeListeners()
{
	GlobalNode::initializeListeners();

	EventListenerPhysicsContact* contactListener = EventListenerPhysicsContact::create();

	contactListener->onContactBegin = CC_CALLBACK_1(CollisionEventDispatcher::onContactBegin, this);
	contactListener->onContactPreSolve = CC_CALLBACK_1(CollisionEventDispatcher::onContactUpdate, this);
	contactListener->onContactPostSolve = CC_CALLBACK_1(CollisionEventDispatcher::onContactUpdate, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(CollisionEventDispatcher::onContactEnd, this);

	this->addEventListener(contactListener);
}

bool CollisionEventDispatcher::onContactBegin(PhysicsContact &contact)
{
	CollisionObject* objectA = dynamic_cast<CollisionObject*>(contact.getShapeA()->getBody()->getNode());
	CollisionObject* objectB = dynamic_cast<CollisionObject*>(contact.getShapeB()->getBody()->getNode());

	if (objectA == nullptr || objectB == nullptr)
	{
		return false;
	}

	// We assume a collision unless either object reports otherwise
	return objectA->onContactBegin(contact) && objectB->onContactBegin(contact);
}

bool CollisionEventDispatcher::onContactUpdate(PhysicsContact &contact)
{
	CollisionObject* objectA = dynamic_cast<CollisionObject*>(contact.getShapeA()->getBody()->getNode());
	CollisionObject* objectB = dynamic_cast<CollisionObject*>(contact.getShapeB()->getBody()->getNode());

	if (objectA == nullptr || objectB == nullptr)
	{
		return false;
	}

	// We assume a collision unless either object reports otherwise
	return objectA->onContactUpdate(contact) && objectB->onContactUpdate(contact);
}

bool CollisionEventDispatcher::onContactEnd(PhysicsContact &contact)
{
	CollisionObject* objectA = dynamic_cast<CollisionObject*>(contact.getShapeA()->getBody()->getNode());
	CollisionObject* objectB = dynamic_cast<CollisionObject*>(contact.getShapeB()->getBody()->getNode());

	if (objectA == nullptr || objectB == nullptr)
	{
		return false;
	}

	// For contact end, the default assumption is no collision, so we trust either of these objects if they report otherwise
	return objectA->onContactEnd(contact) || objectB->onContactEnd(contact);
}
