#include "EntityMovementCollisionBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string EntityMovementCollisionBehavior::MapKey = "entity-movement-collisions";

EntityMovementCollisionBehavior* EntityMovementCollisionBehavior::create(GameObject* owner)
{
	EntityMovementCollisionBehavior* instance = new EntityMovementCollisionBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityMovementCollisionBehavior::EntityMovementCollisionBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->movementCollision = nullptr;

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

EntityMovementCollisionBehavior::~EntityMovementCollisionBehavior()
{
	if (this->movementCollision != nullptr && this->movementCollision->getParent() != nullptr && this->movementCollision->getParent() != this)
	{
		this->movementCollision->getParent()->removeChild(this->movementCollision);
	}
}

void EntityMovementCollisionBehavior::onLoad()
{
	this->defer([=]()
	{
		this->buildMovementCollision();
		this->toggleQueryable(true);
	});
}

void EntityMovementCollisionBehavior::onDisable()
{
	super::onDisable();
	
	if (this->movementCollision != nullptr)
	{
		this->movementCollision->setPhysicsEnabled(false);
	}
}

void EntityMovementCollisionBehavior::update(float dt)
{
}

void EntityMovementCollisionBehavior::buildMovementCollision()
{
	if (this->movementCollision != nullptr)
	{
		return;
	}

	CollisionType collisionType = CollisionType(PlatformerCollisionType::Force);

	this->movementCollision = CollisionObject::create(
		CollisionObject::createBox(this->entity->getEntitySize()),
		// CollisionObject::createCapsulePolygon(this->entity->getEntitySize(), 8.0f),
		collisionType,
		CollisionObject::Properties(true, false),
		Color4F::BLUE
	);
	
	this->movementCollision->setName("entity movement");

	Vec2 collisionOffset = this->entity->getCollisionOffset();
	Vec2 offset = collisionOffset + Vec2(0.0f, this->entity->getEntitySize().height / 2.0f);

	this->movementCollision->setPosition(offset);

	this->addChild(this->movementCollision);
}
