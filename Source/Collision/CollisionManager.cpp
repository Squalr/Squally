#include "CollisionManager.h"

CollisionManager* CollisionManager::create()
{
	CollisionManager* collisionManager = new CollisionManager();

	collisionManager->autorelease();

	return collisionManager;
}

void CollisionManager::initializeEventListeners()
{
	EventListenerPhysicsContact* contactListener = EventListenerPhysicsContact::create();

	contactListener->onContactBegin = CC_CALLBACK_1(CollisionManager::onContactBegin, this);
	contactListener->onContactPreSolve = CC_CALLBACK_1(CollisionManager::onContactUpdate, this);
	// contactListener->onContactPostSolve = CC_CALLBACK_1(CollisionManager::onContactUpdate, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(CollisionManager::onContactEnd, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}

bool CollisionManager::onContactBegin(PhysicsContact &contact)
{
	PhysicsShape* other = nullptr;// Collision::GetCollidingObject(this->physicsBody, contact);

	if (other == nullptr)
	{
		return true;
	}

	return true;
}

bool CollisionManager::onContactUpdate(PhysicsContact &contact)
{
	PhysicsShape* other = nullptr;// Collision::GetCollidingObject(this->physicsBody, contact);

	if (other == nullptr)
	{
		return true;
	}

	return true;
}

bool CollisionManager::onContactEnd(PhysicsContact &contact)
{
	PhysicsShape* other = nullptr;//Collision::GetCollidingObject(this->physicsBody, contact);

	if (other == nullptr)
	{
		return true;
	}

	return true;
}