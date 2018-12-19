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
	CollisionObject* object = dynamic_cast<CollisionObject*>(contact.getShapeA()->getBody()->getNode());

	if (object == nullptr)
	{
		return false;
	}

	return object->onContactBegin(contact);
}

bool CollisionEventDispatcher::onContactUpdate(PhysicsContact &contact)
{
	CollisionObject* object = dynamic_cast<CollisionObject*>(contact.getShapeA()->getBody()->getNode());

	if (object == nullptr)
	{
		return false;
	}

	return object->onContactUpdate(contact);
}

bool CollisionEventDispatcher::onContactEnd(PhysicsContact &contact)
{
	CollisionObject* object = dynamic_cast<CollisionObject*>(contact.getShapeA()->getBody()->getNode());

	if (object == nullptr)
	{
		return false;
	}

	return object->onContactEnd(contact);
}
