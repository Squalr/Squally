#include "CollisionObject.h"

std::string CollisionObject::KeyTypeCollision = "collision";

CollisionObject::CollisionObject(ValueMap* initProperties) : SerializableObject(initProperties)
{
}

CollisionObject::~CollisionObject()
{
}

void CollisionObject::init(PhysicsBody* initPhysicsBody, CategoryGroup initCategoryGroup, bool isDynamic, bool canRotate)
{
	this->physicsBody = initPhysicsBody;
	this->categoryGroup = initCategoryGroup;

	this->physicsBody->setRotationEnable(canRotate);
	this->physicsBody->setDynamic(isDynamic);
	this->setPhysicsBody(initPhysicsBody);

	this->physicsBody->setCategoryBitmask(this->categoryGroup);
	this->physicsBody->setCollisionBitmask(this->getCollisionGroups());
	this->physicsBody->setContactTestBitmask(0xFFFFFFFF);

	this->scheduleUpdate();
}

void CollisionObject::onEnter()
{
	SerializableObject::onEnter();

	this->initializeEventListeners();
}

void CollisionObject::update(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Vec2 pos = this->getPosition();

	const float STOP_PHYSICS_OFFSET = 1024.0f;

	if (this->physicsBody->isDynamic())
	{
		Vec2 cameraPosition = GameCamera::getInstance()->getCameraPosition();

		if (pos.x > cameraPosition.x + visibleSize.width + STOP_PHYSICS_OFFSET ||
			pos.x < cameraPosition.x - STOP_PHYSICS_OFFSET ||
			pos.y > cameraPosition.y + visibleSize.height + STOP_PHYSICS_OFFSET ||
			pos.y < cameraPosition.y - STOP_PHYSICS_OFFSET)
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
	this->physicsBody->setEnabled(enabled);
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

void CollisionObject::initializeEventListeners()
{
	EventListenerPhysicsContact * contactListener = EventListenerPhysicsContact::create();

	contactListener->onContactBegin = CC_CALLBACK_1(CollisionObject::onContactBegin, this);
	contactListener->onContactPreSolve = CC_CALLBACK_1(CollisionObject::onContactUpdate, this);
	contactListener->onContactPostSolve = CC_CALLBACK_1(CollisionObject::onContactUpdate, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(CollisionObject::onContactEnd, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
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

CategoryGroup CollisionObject::getCollisionGroups()
{
	switch (this->categoryGroup)
	{
	case CategoryGroup::G_Solid:
		return (CategoryGroup)(
			CategoryGroup::G_Player
			| CategoryGroup::G_Npc
			| CategoryGroup::G_Enemy
			| CategoryGroup::G_EnemyFlying
			| CategoryGroup::G_Force
			);
	case CategoryGroup::G_PassThrough:
		return (CategoryGroup)(
			CategoryGroup::G_Player
			| CategoryGroup::G_Npc
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
	case CategoryGroup::G_Npc:
		return (CategoryGroup)(
			CategoryGroup::G_Solid
			| CategoryGroup::G_PassThrough
			| CategoryGroup::G_SolidNpc
			);
	case CategoryGroup::G_Enemy:
		return (CategoryGroup)(
			CategoryGroup::G_Player
			| CategoryGroup::G_Solid
			| CategoryGroup::G_PassThrough
			| CategoryGroup::G_SolidNpc
			| CategoryGroup::G_Lava
			);
	case CategoryGroup::G_EnemyFlying:
		return (CategoryGroup)(
			CategoryGroup::G_Player
			| CategoryGroup::G_Solid
			| CategoryGroup::G_PassThrough
			| CategoryGroup::G_SolidNpc
			| CategoryGroup::G_SolidFlyingNpc
			| CategoryGroup::G_Lava
			);
	case CategoryGroup::G_Force:
		return (CategoryGroup)(
			CategoryGroup::G_Player
			| CategoryGroup::G_Solid
			| CategoryGroup::G_PassThrough
			| CategoryGroup::G_SolidNpc
			| CategoryGroup::G_SolidFlyingNpc
			| CategoryGroup::G_Lava
			);
	case CategoryGroup::G_SolidNpc:
		return (CategoryGroup)(
			CategoryGroup::G_Npc
			| CategoryGroup::G_Enemy
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
