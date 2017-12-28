#include "CollisionObject.h"

CollisionObject::CollisionObject()
{
}

CollisionObject::~CollisionObject()
{
}

void CollisionObject::init(PhysicsBody* initPhysicsBody, CategoryGroup initCategoryGroup, bool isDynamic)
{
	this->physicsBody = initPhysicsBody;
	this->categoryGroup = initCategoryGroup;

	this->physicsBody->setRotationEnable(false);
	this->physicsBody->setDynamic(isDynamic);
	this->setPhysicsBody(initPhysicsBody);

	this->physicsBody->setCategoryBitmask(this->categoryGroup);
	this->physicsBody->setCollisionBitmask(this->getCollisionGroups());
	this->physicsBody->setContactTestBitmask(0xFFFFFFFF);

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

CategoryGroup CollisionObject::getCategoryGroup()
{
	return this->categoryGroup;
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

bool CollisionObject::hasSelfHandlingCollision()
{
	switch (this->categoryGroup)
	{
	case CategoryGroup::G_Player:
	case CategoryGroup::G_Enemy:
	case CategoryGroup::G_EnemyFlying:
	case CategoryGroup::G_Force:
		return true;
	default:
		return false;
	}
}

void CollisionObject::initializeEventListeners()
{
	if (this->hasSelfHandlingCollision())
	{
		EventListenerPhysicsContact * contactListener = EventListenerPhysicsContact::create();

		contactListener->onContactBegin = CC_CALLBACK_1(CollisionObject::onContactBegin, this);
		contactListener->onContactPreSolve = CC_CALLBACK_1(CollisionObject::onContactUpdate, this);
		contactListener->onContactPostSolve = CC_CALLBACK_1(CollisionObject::onContactUpdate, this);
		contactListener->onContactSeparate = CC_CALLBACK_1(CollisionObject::onContactEnd, this);

		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
	}
}

bool CollisionObject::onContactBegin(PhysicsContact &contact)
{
	CollisionData data = this->constructCollisionData(contact);

	if (data.other == nullptr)
	{
		return true;
	}

	return this->contactBegin(data);
}

bool CollisionObject::onContactUpdate(PhysicsContact &contact)
{
	CollisionData data = this->constructCollisionData(contact);

	if (data.other == nullptr)
	{
		return true;
	}

	return this->contactUpdate(data);
}

bool CollisionObject::onContactEnd(PhysicsContact &contact)
{
	CollisionData data = this->constructCollisionData(contact);

	if (data.other == nullptr)
	{
		return true;
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

CategoryGroup CollisionObject::getCollisionGroups()
{
	switch (this->categoryGroup)
	{
	case CategoryGroup::G_Solid:
		return (CategoryGroup)(
			CategoryGroup::G_Player
			| CategoryGroup::G_Enemy
			| CategoryGroup::G_EnemyFlying
			| CategoryGroup::G_Force
			);
	case CategoryGroup::G_PassThrough:
		return (CategoryGroup)(
			CategoryGroup::G_Player
			| CategoryGroup::G_Enemy
			| CategoryGroup::G_EnemyFlying
			| CategoryGroup::G_Force
			);
	case CategoryGroup::G_Player:
		return (CategoryGroup)(
			CategoryGroup::G_Enemy
			| CategoryGroup::G_Force
			| CategoryGroup::G_EnemyFlying
			| CategoryGroup::G_Solid
			| CategoryGroup::G_PassThrough
			| CategoryGroup::G_SolidNpc
			| CategoryGroup::G_Lava
			);
	case CategoryGroup::G_Enemy:
		return (CategoryGroup)(
			CategoryGroup::G_Player
			| CategoryGroup::G_Force
			| CategoryGroup::G_Solid
			| CategoryGroup::G_PassThrough
			| CategoryGroup::G_SolidNpc
			| CategoryGroup::G_Lava
			);
	case CategoryGroup::G_EnemyFlying:
		return (CategoryGroup)(
			CategoryGroup::G_Player
			| CategoryGroup::G_Force
			| CategoryGroup::G_Solid
			| CategoryGroup::G_PassThrough
			| CategoryGroup::G_SolidNpc
			| CategoryGroup::G_SolidFlyingNpc
			| CategoryGroup::G_Lava
			);
	case CategoryGroup::G_Force:
		return (CategoryGroup)(
			CategoryGroup::G_Player
			| CategoryGroup::G_Enemy
			| CategoryGroup::G_EnemyFlying
			| CategoryGroup::G_Solid
			| CategoryGroup::G_PassThrough
			| CategoryGroup::G_SolidNpc
			| CategoryGroup::G_SolidFlyingNpc
			| CategoryGroup::G_Lava
			);
	case CategoryGroup::G_SolidNpc:
		return (CategoryGroup)(
			CategoryGroup::G_Enemy
			| CategoryGroup::G_EnemyFlying
			);
	case CategoryGroup::G_SolidFlyingNpc:
		return (CategoryGroup)(
			CategoryGroup::G_EnemyFlying
			);
	case CategoryGroup::G_Water:
		return (CategoryGroup)(
			CategoryGroup::G_Player
			| CategoryGroup::G_Enemy
			);
	case CategoryGroup::G_Lava:
		return (CategoryGroup)(
			CategoryGroup::G_Player
			| CategoryGroup::G_Enemy
			);
	default:
		return CategoryGroup::G_None;
	}
}
