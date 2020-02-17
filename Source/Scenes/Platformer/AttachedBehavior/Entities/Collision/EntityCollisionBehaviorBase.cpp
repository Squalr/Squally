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

void EntityCollisionBehaviorBase::buildEntityCollision()
{
	this->entityCollision = CollisionObject::create(
		CollisionObject::createCapsulePolygon(this->entity->getEntitySize(), 0.9f, 8.0f, 0.0f),
		(CollisionType)this->collisionType,
		CollisionObject::Properties(false, false)
	);

	Vec2 collisionOffset = this->entity->getCollisionOffset();

	if (this->entity->isFlippedY())
	{
		Vec2 offset = Vec2(collisionOffset.x, -collisionOffset.y) - Vec2(0.0f, this->entity->getMovementSize().height / 2.0f);
		this->entityCollision->inverseGravity();
		this->entityCollision->setPosition(offset);
	}
	else
	{
		Vec2 offset = collisionOffset + Vec2(0.0f, this->entity->getMovementSize().height / 2.0f);
		this->entityCollision->setPosition(offset);
	}

	this->addChild(this->entityCollision);

	this->onEntityCollisionCreated();
}
