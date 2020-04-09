#include "EntityCollisionBehaviorBase.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/EngineCollisionTypes.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

EntityCollisionBehaviorBase::EntityCollisionBehaviorBase(GameObject* owner, int collisionType) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->collisionType = collisionType;
	this->entityCollision = nullptr;

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->toggleQueryable(false);
}

EntityCollisionBehaviorBase::~EntityCollisionBehaviorBase()
{
}

void EntityCollisionBehaviorBase::onLoad()
{
	this->defer([=]()
	{
		this->buildEntityCollision();
		this->toggleQueryable(true);
	});
}

void EntityCollisionBehaviorBase::onDisable()
{
	super::onDisable();
	
	if (this->entityCollision != nullptr)
	{
		this->entityCollision->setPhysicsEnabled(false);
	}
}

void EntityCollisionBehaviorBase::buildEntityCollision()
{
	if (this->isInvalidated())
	{
		return;
	}

	this->entityCollision = CollisionObject::create(
		CollisionObject::createCapsulePolygon(this->entity->getEntitySize() * 0.9f, 8.0f),
		(CollisionType)this->collisionType,
		CollisionObject::Properties(false, false)
	);

	Vec2 collisionOffset = this->entity->getCollisionOffset();
	Vec2 offset = collisionOffset + Vec2(0.0f, this->entity->getMovementSize().height / 2.0f);

	this->entityCollision->setPosition(offset);

	this->addChild(this->entityCollision);

	this->onEntityCollisionCreated();
}
